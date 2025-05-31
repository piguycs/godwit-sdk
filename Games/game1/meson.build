headers = include_directories('include/')

game1_src = [
    'main.cpp',
]

executable('game1', game1_src,
    dependencies: sdk_core_dep,
    include_directories: headers,
    install: true,
    win_subsystem: 'windows',
)
