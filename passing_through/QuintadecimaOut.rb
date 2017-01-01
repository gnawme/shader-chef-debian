require 'matrix.rb'

#
#	Generates 15th tiling pentagon from vertices derived by construction
#
def layout
  quinpts = [
    Vector[2.0, 0.0],
    Vector[(1.0 + (1.0/2.0)), 55.0/64.0],
    Vector[-11.0/32.0, 1.0 + (23.0/64.0)],
    Vector[-55.0/64.0, 0.5],
    Vector[0.0, 0.0]
  ]

  quinpts.each_index do |idx|
    quinpts[idx] /= 2.0
  end

  labels = ['A', 'B', 'C', 'D', 'E']

  puts "Uncentered points"
  quinpts.each_index do |idx|
    puts "Point #{labels[idx]} #{quinpts[idx]}"
  end

end

layout
