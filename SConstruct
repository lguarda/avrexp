import yaml
import os

with open("target_definition.yaml", "r") as stream:
  definition = yaml.safe_load(stream)

# definition_parmeters =  [f'{key}:: {value}' for key, value in definition['parameters'].items()]
definition_parmeters = ['%s=%s' % (key, value) for (key, value) in definition['parameters'].items()]

device = definition['device']

TARGET = 'build/main.elf'
TARGET_HEX = 'build/main.hex'
TARGET_INFO = 'build/main.info'

env = Environment()

# enable color ouput
if 'TERM' in os.environ:
  env['ENV']['TERM'] = os.environ['TERM']

# Set environment for AVR-GCC.
env['CC'] = 'avr-gcc'
env['CXX'] = 'avr-g++'
env['AS'] = 'avr-gcc'
env['OBJCOPY'] = 'avr-objcopy'
env['SIZE'] = 'avr-size'
env.Append(CCFLAGS = '-Os -Wall -Werror -Wno-array-bounds')
env.Append(CCFLAGS = '-mmcu=' + device)
env.Append(LINKFLAGS = '-mmcu=' + device)
# env.Append(LINKFLAGS = '-Wl,-u,vfprintf -lprintf_min')
# env.Append(LINKFLAGS = '-lm')
env.Append(CPPDEFINES = definition_parmeters)

sources = [
    'src/running_i2c.c',
    'src/twi_master.c',
    'src/lcd_command.c',
    'src/mcp23017.c',
    ]

Default(env.Program(target = TARGET, source = sources))
Default(env.Command(TARGET_HEX, TARGET, env['OBJCOPY'] + ' -j .text -j .data -O ihex $SOURCE $TARGET'))
Default(env.Command(TARGET_INFO, TARGET, env['SIZE'] + ' -C --mcu=' + device + ' $SOURCE | tee $TARGET'))
flash = env.Command(None, [TARGET_HEX, TARGET_INFO], 'avrdude -c um232h -p attiny88 -v -U flash:w:' + TARGET_HEX)

env.Alias('flash', flash)
