file size of bands: 81.5kb
file size of fractals: 208.0kb
Takes as command line inputs ./converter "filename".pgm. It skips the P5 200 200 255 and starts to get each byte afterwards. Each byte=R=G=B, with a=ff. I shifted and used bitwise operators to create the data commands for RGBa. Then increment the tx position by 1 after each RGBa. Lastly it writes commands for a line once at the end of the row and then moves on to the beginning of the next row.
