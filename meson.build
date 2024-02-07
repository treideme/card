project('MSP430 Template', 
	'c',
	version : '0.1',
	default_options : [ 
		'buildtype=minsize', 
		'c_std=c99',
	],
)

assert(meson.is_cross_build(), 'Use cross-build for MSP430 target')

#msp430flasher = find_program('msp430flasher', required : true)
objcopy = find_program('msp430-elf-objcopy', required : true)
objdump = find_program('msp430-elf-objdump', required : true)
# gdbserver = find_program('gdb_agent_console', required: true)

incdir = [
	#include_directories('inc'),
	#include_directories('usb'),
	get_option('MSP430HOME')+'/include/',
]

t_executable = '@0@.elf'
t_bin = '@0@.bin'
t_hex = '@0@.hex'
t_asm = '@0@.S'
t_flash = 'flash_@0@'

t_mspchip = '-mmcu=@0@'
t_mapfile = '-Wl,-Map,@0@.map'

#subdir('driverlib')
#subdir('usb')

progs = [
	['business_card', [
		 'main.c',
		 'hardware.c',
		 'interrupts.c',
		 'i2c.c',
		 'st25dv.c',
		 'uart.c'],
	 'Business Card',
	 'msp430g2553'],
]

#debug = run_target('debug',
#		command : [gdbserver, get_option('MSP430HOME')+'/msp430.dat'],
#)

foreach p : progs

	exe = executable(t_executable.format(p[0]), p[1],
		c_args : t_mspchip.format(p[3]),
		link_args : [t_mapfile.format(p[0]),
		    '-L'+get_option('MSP430HOME')+'/include/', t_mspchip.format(p[3])],
		include_directories : [incdir],
		build_by_default : true,
	)
	bin = custom_target(t_bin.format(p[0]),
		output : [t_bin.format(p[0])],
		build_by_default : true,
		command : [objcopy, '-O', 'binary', t_executable.format(p[0]), t_bin.format(p[0])],
        depends : exe)
	hex = custom_target(t_hex.format(p[0]),
		output : [t_hex.format(p[0]),],
        build_by_default : true,
        command : [objcopy, '-O', 'ihex', t_executable.format(p[0]), t_hex.format(p[0])],
        depends : exe)
	asm = custom_target(t_asm.format(p[0]),
		output : t_asm.format(p[0]),
        build_by_default : true,
        command : [objdump, '-d', '-S', t_executable.format(p[0])],
		capture : true,
        depends : exe)
#    flash = run_target(t_flash.format(p[0]),
#		command : [msp430flasher, '-e', 'ERASE_ALL', '-v', '-w', t_hex.format(p[0])],
#		depends : hex,
#	)
endforeach