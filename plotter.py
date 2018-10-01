from gmplot import gmplot

plotData = open('C++_BruinNav_Implementation/output.txt','r')

# Place map
gmap = gmplot.GoogleMapPlotter(34.068921, -118.445181, 13)

input_zip = []
for line in plotData:
	input_zip.append(map(float, line.strip().split(',')))

input_zip = [tuple(l) for l in input_zip]


lawae_lats, lawae_lons = zip(*input_zip)

gmap.plot(lawae_lats, lawae_lons, 'cornflowerblue', edge_width=10)

# Draw
gmap.draw("my_map.html")