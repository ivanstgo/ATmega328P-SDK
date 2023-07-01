TARGET = ports
MCU = atmega328p
FCPU = 16000000UL
FORMAT = ihex

SRC_DIR = src
INC_DIR = ../../include
BIN_DIR = build
OBJ_DIR = $(BIN_DIR)/objects
LST_DIR = $(BIN_DIR)/listings

CSRC = ports_example.c \
	   ../../src/ports.c
ASRC = $(wildcard .../$(SRC_DIR)/*.S)

CC = avr-gcc
OBJCOPY = avr-objcopy
OBJDUMP = avr-objdump
SIZE = avr-size
NM = avr-nm
AVRDUDE = avrdude
REMOVE = rm -frv

# ************************** AVRDUDE CONFIGURATION ***************************
AVRDUDE_PROGRAMMER = arduino
AVRDUDE_PORT = /dev/ttyACM0
AVRDUDE_BASIC = -p $(MCU) -P $(AVRDUDE_PORT) -c $(AVRDUDE_PROGRAMMER)
AVRDUDE_WRITE_FLASH = -U flash:w:$(BIN_DIR)/$(TARGET).hex
#AVRDUDE_WRITE_EEPROM = -U eeprom:w:$(BIN_DIR)/$(TARGET).eep
AVRDUDE_VERBOSE = -v
AVRDUDE_FLAGS = $(AVRDUDE_BASIC) $(AVRDUDE_VERBOSE)

# ****************************** COMPILER FLAGS ******************************
CSTANDARD =
CINCS = $(INC_DIR)
CDEBUG = -g
CDEFS = -DF_CPU=${FCPU}
OPT = s
CWARN = -Wall -Wstrict-prototypes
CTUNING = -funsigned-char -funsigned-bitfields -fpack-struct -fshort-enums
#CEXTRA = -Wa,-adhlns=$(<:.c=.lst)
CFLAGS = $(CINCS) $(CDEBUG) $(CDEFS) -O$(OPT) $(CWARN) $(CSTANDARD) $(CEXTRA)
#ASFLAGS = -Wa,-adhlns=$(<:.S=.lst),-gstabs 
LDFLAGS = 
ALL_CFLAGS = -mmcu=$(MCU) -I$(CFLAGS)
ALL_ASFLAGS = -mmcu=$(MCU) -I. -x assembler-with-cpp $(ASFLAGS)

# ******************* DEFINE ALL OBJECT AND LISTING FILES ********************
OBJ = $(ASRC:%.S=$(OBJ_DIR)/%.o) $(CSRC:%.c=$(OBJ_DIR)/%.o)
LST = $(ASRC:%.S=$(LST_DIR)/%.lst) $(CSRC:%.c=$(LST_DIR)/%.lst)

# ****************************** DEFAULT TARGET ******************************
all: build info

build: elf hex lss sym

elf: $(BIN_DIR)/$(TARGET).elf
hex: $(BIN_DIR)/$(TARGET).hex
eep: $(BIN_DIR)/$(TARGET).eep
lss: $(BIN_DIR)/$(TARGET).lss
sym: $(BIN_DIR)/$(TARGET).sym

.SUFFIXES: .elf .hex .eep .lss .sym

.elf.hex:
	$(OBJCOPY) -O $(FORMAT) -R .eeprom $< $@

.elf.eep:
	$(OBJCOPY) -j .eeprom --set-section-flags=.eeprom="alloc,load" \
	--change-section-lma .eeprom=0 -O $(FORMAT) $< $@

.elf.lss:
	$(OBJDUMP) -h -S $< > $@

.elf.sym:
	$(NM) -n $< > $@

# *************************** LINK .ELF FROM .OBJ ****************************
$(BIN_DIR)/$(TARGET).elf: $(OBJ)
	$(CC) $(ALL_CFLAGS) $(OBJ) --output $@ $(LDFLAGS)

# *************************** COMPILE .OBJ FROM .C ***************************
$(OBJ_DIR)/%.o: %.c
	@mkdir -p $(@D)
	$(CC) -c $(ALL_CFLAGS) $< -o $@ 

# **************************** COMPILE .S FROM .C ****************************
$(OBJ_DIR)/%.s: %.c
	@mkdir -p $(@D)
	$(CC) -S $(ALL_CFLAGS) $< -o $@

# *************************** ASSEMBLE .O FROM .S ****************************
$(OBJ_DIR)/%.o: %.S
	@mkdir -p $(@D)
	$(CC) -c $(ALL_ASFLAGS) $< -o $@

# ****************************** PROGRAM DEVICE ******************************
upload: $(BIN_DIR)/$(TARGET).hex $(BIN_DIR)/$(TARGET).eep
	@clear
	$(AVRDUDE) $(AVRDUDE_FLAGS) $(AVRDUDE_WRITE_FLASH) $(AVRDUDE_WRITE_EEPROM)

# *************************** DISPLAY PROGRAM SIZE ***************************
info: $(BIN_DIR)/$(TARGET).elf
	@echo ""
	@$(SIZE) --format=avr --mcu=$(MCU) $(BIN_DIR)/$(TARGET).elf

# **************************** CLEAN BUILD FILES *****************************
clean:
	@$(REMOVE) $(BIN_DIR)/$(TARGET).hex $(BIN_DIR)/$(TARGET).eep \
	$(BIN_DIR)/$(TARGET).sym $(BIN_DIR)/$(TARGET).lss \
	$(BIN_DIR)/$(TARGET).elf $(OBJ_DIR)

.PHONY: all build elf hex eep lss sym upload clean info