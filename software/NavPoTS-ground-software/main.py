"""i would put a list of todos in here, but theres so much im not even going to bother, ill figure it out"""

import re
from collections import deque
import serial
from textual.app import App, ComposeResult
from textual.containers import Horizontal, Vertical
from textual.widgets import Static, Footer
from textual.reactive import reactive
from textual import work

############## Config #################

SERIAL_PORT = "/dev/ttyACM0"
BAUD_RATE = 115200

UART_REGEX = re.compile(r"(\w+)\s+(-?\d+\.\d+)")

HISTORY_LENGTH = 25
DATA_BOX_WIDTH = 12
DATA_BOX_HEIGHT = HISTORY_LENGTH + 2

############## Widgets ################

class DATA_BOX(Static):
    history: reactive[tuple] = reactive(tuple())

    def __init__(self, data_label: str, precision: int = 3, **kwargs):
        super().__init__(**kwargs)
        self.data_label = data_label
        self.precision = precision
        self._buf: deque[float] = deque(maxlen=HISTORY_LENGTH)

    def push(self, value: float) -> None:
        self._buf.append(value)
        self.history = tuple(self._buf)

    def render(self) -> str:
        lines = [f"[bold red]{self.data_label}[/]", ""]

        for i in reversed(self.history):
            lines.append(f"{i: .{self.precision}f}")

        while len(lines) < HISTORY_LENGTH + 2:
            lines.append("")

        return "\n".join(lines)

class SENSOR_GROUP(Vertical):

    def __init__(self, title: str, axes: list[str], unit: str = "", precision: int = 3, **kwargs):
        super().__init__(**kwargs)
        self.title = title
        self.axes = axes
        self.unit = unit
        self.precision = precision

    def compose(self) -> ComposeResult:
        label = f"{self.title} ({self.unit})" if self.unit else self.title
        yield Static(label, classes="group-title")

        with Horizontal(classes="axis-row"):
            for axis in self.axes:
                yield DATA_BOX(axis, precision=self.precision, id=axis)

############## APP #####################

class NAVPOTS_DASHBOARD(App):

    CSS = f"""

    #title {{
        border: heavy white;
        height: 3;
        content-align: center middle;
        background: black;
        text-style: bold;
    }}

    #sensor {{
        border: heavy white;
        height: auto;
        width: auto;
        padding: 0 1;
    }}

    #sensor_data_box {{
        layout: horizontal;
        height: auto;
    }}

    .sensor-title {{
        height: 1;
        background: black;
        text-style: bold;
    }}

    .group-title {{
        text-style: bold underline;
        content-align: center middle;
        height: 1;
        width: 100%;
    }}
    
   .axis-row {{
        height: auto;
        width: auto;
    }}

    SENSOR_GROUP {{
        border: heavy white;
        height: auto;
        width: auto;
        margin: 0 1 0 0;
        padding: 0 1;
    }}


    DATA_BOX {{
        height: {DATA_BOX_HEIGHT};
        width: {DATA_BOX_WIDTH};
        content-align: left top;
        background: black;
        padding-left: 1;
        margin: 0 1 0 0;
    }}

    DATA_BOX:last-of-type {{
        margin: 0;
    }}
    """

    def compose(self) -> ComposeResult:
        yield Static("[red bold]NavPoTS Ground Software - v0.0.1[/]", id="title")

        with Vertical(id="sensor"):
            yield Static("[red bold]ASM330LHHXTR[/]", classes="sensor-title")
            with Horizontal(id="sensor_data_box"):
                yield SENSOR_GROUP("Temperature", ["temp"], unit="C", precision=3)
                yield SENSOR_GROUP("Gyroscope", ["gx", "gy", "gz"], unit="deg/s", precision=3)
                yield SENSOR_GROUP("Accelerometer", ["ax", "ay", "az"], unit="g", precision=3)
        yield Footer()

    def on_mount(self) -> None:
        self.read_uart()

    @work(thread=True, exclusive=True)
    def read_uart(self) -> None:
        serial_stream = serial.Serial(SERIAL_PORT, BAUD_RATE, timeout=1)
        while True:
            raw = serial_stream.readline().decode(errors="ignore").strip()

            if not raw:
                continue

            pairs = dict(UART_REGEX.findall(raw))

            if pairs:
                self.call_from_thread(self.update_values, pairs)

    def update_values(self, pairs: dict) -> None:
        for key, value in pairs.items():
            try:
                box = self.query_one(f"#{key}", DATA_BOX)
                box.push(float(value))
            except Exception:
                continue

    def on_key(self, event):
        match event.key:
            case "q":
                exit()

if __name__ == "__main__":
    NAVPOTS_DASHBOARD().run()
