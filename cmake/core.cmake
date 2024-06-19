function(install_binaries target binaries_dir)
    add_custom_command(
            TARGET "${target}" POST_BUILD
            COMMAND ${CMAKE_COMMAND} -E copy_directory
            "${binaries_dir}/bin/$<CONFIGURATION>"
            $<TARGET_FILE_DIR:${target}>
    )
endfunction()
