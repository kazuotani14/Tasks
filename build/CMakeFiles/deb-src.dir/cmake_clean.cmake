file(REMOVE_RECURSE
  "doc/Tasks.doxytag"
  "doc/doxygen.log"
  "doc/doxygen-html"
  "CMakeFiles/deb-src"
)

# Per-language clean rules from dependency scanning.
foreach(lang )
  include(CMakeFiles/deb-src.dir/cmake_clean_${lang}.cmake OPTIONAL)
endforeach()
