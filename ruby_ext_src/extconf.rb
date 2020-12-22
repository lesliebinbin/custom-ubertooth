require 'mkmf-rice'
dir_config('custom_ubertooth', File.expand_path('../custom_ubertooth/includes'), File.expand_path('../build/custom_ubertooth'))
puts have_library('custom_ubertooth')
create_makefile('build/ubertooth_ext')
