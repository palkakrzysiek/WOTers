M5 -- Thinning
==============
* This method creates skeleton of the image, that means only objects that are
  1 px width.
* Time of execution depends on content of the image.
* In every iteration there are applied HMT operation with such structural
  objects, that "eats" borders, so:
* The bigger white object in the image, the greater number of iterations.
* Good method for OCR
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
* New intensity values of neighbors will have value 255.
* Pixels considered not as neighbors will get value 0.
* If given image is colored, the it will be converted to gray scale by taking
  average mean of all channels.
* Implementation will consists of iteration of all pixels to find seeds, those
  pixels will be added to the queue (other will get value 0 -- on separate
  image). Then their (those with value 255 neighbors will be checked if
  their not belongs to the same region, if they are, they'll be added to queue.
  And value of output image will be set to 255
* Only pixels with values different than 255 on output image) can be added to
  queue (except of the first iteration) to prevent infinite execution (if they
  have value 255 on output image, that means they have already been checked).
* When queue will be empty loop that checks values forom queue terminates and
  temporary, monochromatic image replaces the old one.

It can be used to extract only pixels within given range, but only if they are
connected with some seed value.
Examples:
Original image
[http://stock-by-kai.deviantart.com/art/Lightning-Original-147408115](http://stock-by-kai.deviantart.com/art/Lightning-Original-147408115):
![lighting](lighting.jpg)
Seed value: 250; tolerance +/- 20:
![1](lighting-s250-th20-out.bmp)
Seed value: 253; tolerance +/- 20:
![2](lighting-s253-th20-out.bmp)
Seed value: 250; tolerance +/- 80:
![3](lighting-s250-th80-out.bmp)
Original:
![4](lena.bmp)
Seed value: 110; tolerance +/- 25, with inverted values, to obtain black
foreground and wihe backgroud:
![5](lena-s110-th25-negative-out.bmp)
