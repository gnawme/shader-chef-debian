require 'matrix.rb'

def layout
  quinpts = [
    Vector[4.0, 0.0],
    Vector[3.0, 1.0 + 45.0/64.0],
    Vector[-47.0/64.0, 2.0 + 47.0 / 64.0],
    Vector[-(1.0 + 47.0/64.0), 1.0],
    Vector[0.0, 0.0]
  ]

  quinpts.each_index do |idx|
    quinpts[idx] /= 4.0
  end

  labels = ['A', 'B', 'C', 'D', 'E']

  puts "Uncentered points"
  quinpts.each_index do |idx|
    puts "Point #{labels[idx]} #{quinpts[idx]}"
  end

end

layout
