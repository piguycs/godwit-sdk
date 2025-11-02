headers = include_directories('include/')

game1_src = [
    'main.cpp',
    'cells.cpp',
    'camera.cpp',
]

executable('lava', game1_src,
    dependencies: sdk_core_dep,
    include_directories: headers,
    install: true,
    win_subsystem: 'windows',
)
