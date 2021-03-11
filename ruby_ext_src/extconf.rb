require 'mkmf-rice'
dir_config('custom_ubertooth', [File.expand_path('../custom_ubertooth/includes'), '/usr/include/libusb-1.0/'], File.expand_path('../build/custom_ubertooth'))
puts have_library('custom_ubertooth')
create_makefile('build/ubertooth_ext')
