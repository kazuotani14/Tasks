file(REMOVE_RECURSE
  "doc/Tasks.doxytag"
  "doc/doxygen.log"
  "doc/doxygen-html"
  "CMakeFiles/distclean"
)

# Per-language clean rules from dependency scanning.
foreach(lang )
  include(CMakeFiles/distclean.dir/cmake_clean_${lang}.cmake OPTIONAL)
endforeach()