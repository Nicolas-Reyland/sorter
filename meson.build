# Meson build file for the 42sh project

project(
    'sorter',
    'cpp',
    default_options : [
        'warning_level=3',
        'cpp_std=c++20',
        'werror=true',
        # Debug
        'buildtype=debug',
        'debug=true',
        'b_sanitize=address',
    ],
)

add_project_arguments('-Wvla', language : 'c')
add_project_arguments('-pedantic', language : 'c')
add_project_arguments('-I../src', language : 'c')

source_files = [
    # Main file
    'main.cpp',
]

source_files_full = []

foreach file : source_files
    full_path = join_paths('src', file)
    source_files_full += files(full_path)
endforeach

executable(
    'sorter',
    source_files_full,
    install : true,
    install_dir : '.',
)
