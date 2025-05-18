headers = include_directories('include/')

game1_src = [
    'main.cpp',
]

# we have to add a WinMain entrypoint for the toy operating system
if host_machine.system() == 'windows'
    game1_src += 'winmain.c'
endif

executable('game1', game1_src,
    dependencies: sdk_core_dep,
    include_directories: headers,
    install: true,
    win_subsystem: 'windows',
)
