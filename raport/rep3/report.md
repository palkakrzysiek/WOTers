M5 -- Thinning
==============
Remember to sometimes invert colors - white is considered as foreground and
black as background
![orig](thinning-in.bmp) ![res](thinning-res.bmp)

Region growing
==============
* Intensity value of the seed points is obtained form the user.
* Intensity value must be in range 0 - 255.
* To reject pixels that could be an noise, there could be used one of
  implemented filters, e.g. alpha-trimmed mean filter with parameter 8 (median
  filter) will be good for impulse noise or, with parameter 0 (mean filter) will
  be good for uniform noise.
* User can set threshold value, say N, then values considered as neighbors
  will be in range seed intensity + N < neighbor < seed intensity - N.
* If user will not set threshold value, it will be calculated basing on mean
  value of all pixels, according to formula |threshold value - mean|.
* New intensity values of neighbors will 0 (black pixels)
* Pixels considered not as neighbors will get value 255 (white)
* If given image is colored, the it will be converted to gray scale by taking
  average mean of all channels.
* Implementation will consists of iteration of all pixels to find seeds, those
  pixels will be added to the queue (other will get value 255 -- on separate
  image). Then their (those with value 0) neighbors will be checked if
  their not belongs to the same region, if they are, they'll be added to queue.
  And value of output image will be set to 0
* Only pixels with values different than 0 (on output image) can be added to
  queue (except of the first iteration) to prevent infinite execution (if they
  have value 0 on output image, that means they have already been checked)
* When queue will be empty loop that checks values forom queue terminates and
* temporary, monochromatic image replaces the old one.
