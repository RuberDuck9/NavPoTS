PROJECT = NavPoTS
BUILD_DIR = bin

CFILES = main.c
CFILES += gpio.c
CFILES += spi.c
CFILES += usart.c
CFILES += clock.c
CFILES += delay.c

DEVICE=stm32h743zit6
OOCD_FILE = board/stm32f4discovery.cfg

VPATH += $(SHARED_DIR)
INCLUDES += $(patsubst %,-I%, . $(SHARED_DIR))
OPENCM3_DIR=../libopencm3

include $(OPENCM3_DIR)/mk/genlink-config.mk
include ../rules.mk
include $(OPENCM3_DIR)/mk/genlink-rules.mk
