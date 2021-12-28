import yaml

with open("target_definition.yaml", "r") as stream:
  definition = yaml.safe_load(stream)

# definition_parmeters =  [f'{key}:: {value}' for key, value in definition['parameters'].items()]
definition_parmeters = ['%s=%s' % (key, value) for (key, value) in definition['parameters'].items()]

device = definition['device']

TARGET = 'build/main'

env = Environment()

# Set environment for AVR-GCC.
env['CC'] = 'avr-gcc'
env['CXX'] = 'avr-g++'
env['AS'] = 'avr-gcc'
env['OBJCOPY'] = 'avr-objcopy'
env['SIZE'] = 'avr-size'
env.Append(CCFLAGS = '-Os -Wall -Werror')
env.Append(CCFLAGS = '-mmcu=' + device)
# env.Append(LINKFLAGS = '-mmcu=' + DEVICE)
# env.Append(LINKFLAGS = '-Wl,-u,vfprintf -lprintf_min')
# env.Append(LINKFLAGS = '-lm')
env.Append(CPPDEFINES = definition_parmeters)

sources = [
    'running_i2c.c',
    'twi_master.c',
    'lcd_command.c',
    ]

Default(env.Program(target = TARGET + '.elf', source = sources))
Default(env.Command(TARGET + '.hex', TARGET + '.elf', env['OBJCOPY'] + ' -O ihex $SOURCE $TARGET'))
Default(env.Command(None, TARGET + '.elf', env['SIZE'] + ' -C --mcu=' + device + ' $SOURCE'))
