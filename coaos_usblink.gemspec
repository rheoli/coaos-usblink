# GEM Spec

Gem::Specification.new do |s|
  s.name        = 'coaos_usblink'
  s.version     = '0.0.1'
  s.date        = '2013-06-10'
  s.summary     = "CoActionOS USB Link Library"
  s.description = "Gem to use the CoActionOS USB Link library"
  s.authors     = ["Stephan Toggweiler"]
  s.email       = 'stephan@rheoli.net'
  s.files       = Dir.glob('lib/**/*.rb') +
                   Dir.glob('ext/**/*.{c,h,rb}')
  s.extensions  = ['ext/coaos_usblink_c/extconf.rb']
  s.homepage    =
    'https://github.com/rheoli/coaos-usblink'
end
