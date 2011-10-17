package magick;


import java.awt.Dimension;
import java.awt.Rectangle;


/**
 * Encapsulation of the ImageMagick Image object.
 * We use MagickImage here so as not to be confused
 * with java.awt.Image.
 *
 * @author Eric Yeo
 */
public class MagickImage extends Magick {

    /**
     * Internal ImageMagick Image handle.
     * We use long (64-bits) for portability.
     */
    private long magickImageHandle = 0;

    /**
     * Constructor.
     */
    public MagickImage()
    {
    }

    /**
     * Construct a MagickImage that is made up of all
     * the images in the specified array. If any of
     * the images contains multiple frames, the frames
     * are also appended to the new image. All the
     * images are cloned.
     * @param images array of images to linked
     */
    public MagickImage(MagickImage[] images)
        throws MagickException
    {
        initMultiImage(images);
    }

    /**
     * Helper for the constcutor to create an image that
     * is made up of all the images in the specified array.
     * If any of  the images contains multiple frames, the
     * frames are also appended to the new image. All the
     * images are cloned.
     * @param images array of images to linked
     * @throws MagickException if the new image cannot be constructed
     * @see MagickImage
     */
    private native void initMultiImage(MagickImage[] images)
        throws MagickException;

    /**
     * Constructor that also reads an image file
     * specified in the parameter.
     *
     * @param imageInfo the ImageInfo for an image file to read
     * @param boolean true for ping the image only.
     *
     * @exception MagickException on error
     */
    public MagickImage(ImageInfo imageInfo, boolean ping)
        throws MagickException
    {
        if (ping) {
            pingImage(imageInfo);
        }
        else {
            readImage(imageInfo);
        }
    }

    /**
     * Pings the image.
     * @param imageInfo the ImageInfo for an image file to read
     * @see <a href="http://www.imagemagick.org/api/constitute.php#PingImage">The underlying ImageMagick call</a>
     */
    public native void pingImage(ImageInfo imageInfo)
        throws MagickException;

    /**
     * Constructor that also reads an image file
     * specified in the parameter.
     *
     * @param imageInfo the ImageInfo for an image file to read
     *
     * @exception MagickException on error on error
     */
    public MagickImage(ImageInfo imageInfo)
	throws MagickException
    {
	readImage(imageInfo);
    }

    /**
     * Constructor that takes the image to be read from memory.
     *
     * @param imageInfo the ImageInfo instance for default settings, etc
     * @param blob the image to be read in memory
     *
     * @exception MagickException on error
     */
    public MagickImage(ImageInfo imageInfo, byte[] blob)
	throws MagickException
    {
	blobToImage(imageInfo, blob);
    }

    /**
     * This method will clean up the handle.
     */
    protected void finalize()
    {
	destroyImages();
    }

    /**
     * Allocate a blank image object.
     *
     * @param imageInfo specifies the parameters for the blank image
     */
    public native void allocateImage(ImageInfo imageInfo);

    /**
     * Read the image specified in the ImageInfo object.
     *
     * @param imageInfo specifies the file to read from
     * @see <a href="http://www.imagemagick.org/api/constitute.php#ReadImage">The underlying ImageMagick call</a>
     * @exception MagickException on error
     */
    public native void readImage(ImageInfo imageInfo)
	throws MagickException;

    /**
     * Write the image specified in the ImageInfo object.
     *
     * @param imageInfo specifies the writing parameters
     *
     * @exception MagickException on error
     */
    public native boolean writeImage(ImageInfo imageInfo)
	throws MagickException;

    /**
     * Return the image file name of the image.
     *
     * @return the file name of the image
     * @exception MagickException on error
     */
    public native String getFileName()
	throws MagickException;

    /**
     * Set the image file name.
     *
     * @param fileName new file name
     *
     * @exception MagickException on error
     */
    public native void setFileName(String fileName)
	    throws MagickException;

    /**
     * Set the filter type.
     *
     * @param filter the filter type from constants defined in the class FilterType
     * @see FilterType
     * @exception MagickException on error
     */
    public native void setFilter(int filter)
	throws MagickException;

    /**
     * Get the filter type.
     *
     * @return the filter type as defined in the class FilterType
     * @see FilterType
     * @exception MagickException on error
     */
    public native int getFilter()
        throws MagickException;

    /**
     * Adds random noise to the image.
     *
     * @param noiseType The type of noise: Uniform, Gaussian, Multiplicative,
     *                  Impulse, Laplacian, or Poisson.
     * @see NoiseType
     * @return An image with additional noise.
     * @see <a href="http://www.imagemagick.org/api/effect.php#AddNoiseImage">The underlying ImageMagick call</a>
     * @exception MagickException on error
     */
    public native MagickImage addNoiseImage(int noiseType)
	    throws MagickException;

    /**
     * Return the number of columns and rows of the image.
     * @return the dimension of the image
     * @exception MagickException on error
     */
    public native Dimension getDimension()
	    throws MagickException;

    /**
     * Return the width of the image.
     *
     * @return the width of the image.
     * @exception MagickException on error
     */
    public native int getWidth()
	    throws MagickException;
    
    /**
     * Return the height of the image.
     *
     * @return the height of the image.
     * @exception MagickException on error
     */
    public native int getHeight()
	    throws MagickException;
    
    /**
     * Return the depth of the image.
     *
     * @return the depth of the image.
     * @exception MagickException on error
     */
    public native int getDepth()
	    throws MagickException;

    /**
     * Set the depth of the image.
     *
     * @param depth the depth of the image
     * @exception MagickException on error
     */
    public native void setDepth(int depth)
      throws MagickException;


    /**
     * Blurs an image. We convolve the image with a Gaussian operator of
     * the given radius and standard deviation (sigma). For reasonable
     * results, the radius should be larger than sigma. Use a radius of 0
     * and BlurImage() selects a suitable radius for you.
     *
     * @param raduis The radius of the gaussian, in pixels, not counting
     *               the center pixel
     * @param sigma The standard deviation of the gaussian, in pixels
     *
     * @return A blurred image.
     * @exception MagickException on error
     */
    public native MagickImage blurImage(double raduis, double sigma)
	throws MagickException;


    /**
     * Blurs an image. We convolve the image with a Gaussian operator of
     * the given radius and standard deviation (sigma). For reasonable
     * results, the radius should be larger than sigma. Use a radius of 0
     * and BlurImage() selects a suitable radius for you.
     *
     * @param channel The channel(s) to which the blurring should apply
	 				 (see ChannelType)
     * @param raduis The radius of the gaussian, in pixels, not counting
     *               the center pixel
     * @param sigma The standard deviation of the gaussian, in pixels
     *
     * @return A blurred image.
     * @exception MagickException on error
     */
    public native MagickImage blurImageChannel(int channel, double raduis, double sigma)
	throws MagickException;

    /**
     * Trim edges that are the background color from the image.
     * @exception MagickException on error
     */
    public native MagickImage trimImage()
      throws MagickException;

/**
     * Return the storage class of the image.
     *
     * @return the store class as defined in ClassType
     * @see ClassType
     * @exception MagickException on error
     */
    public native int getStorageClass()
	throws MagickException;

    /*
     * Annotates an image with test. Optionally the annotation can
     * include the image filename, type, width, height, or scene
     * number by embedding special format characters.
     *
     * @param info the anotation information
     */
    public native void annotateImage(DrawInfo info);

    /**
     * Surrounds the image with a border of the color defined by
     * the border color member of the image structure. The width
     * and height of the border are defined by the corresponding
     * members of the Rectangle.
     *
     * @param borderInfo the rectangle for which border is drawn
     * @return an Image with a border around it
     * @exception MagickException on error
     * @see #setBorderColor
     * @see #getBorderColor
     */
    public native MagickImage borderImage(Rectangle borderInfo)
	throws MagickException;

    /**
     * Creates a new image that is a copy of an existing one with the
     * edges highlighted, producing a 'charcoal-drawing' effect.
     *
     * @param raduis The radius of the pixel neighborhood.
     * @param sigma The standard deviation of the gaussian, in pixels
     *
     * @return A charcoal-like image.
     * @exception MagickException on error
     */
    public native MagickImage charcoalImage(double raduis, double sigma)
	throws MagickException;

    /**
     * Creates a simulated three-dimensional button-like effect by
     * lightening and darkening the edges of the image. Members width
     * and height of raiseInfo define the width of the vertical and
     * horizontal edge of the effect.
     *
     * @param raiseInfo the rectangle for which border is drawn
     * @param raise true to create raise effect, false to lower
     * @return true if successful, false otherwise
     * @exception MagickException on error
     */
    public native boolean raiseImage(Rectangle raiseInfo, boolean raise)
	throws MagickException;

    /**
     * Creates a new image that is a subregion of the original.
     *
     * @param chopInfo the rectange to chop the image
     * @exception MagickException on error
     */
    public native MagickImage chopImage(Rectangle chopInfo)
	throws MagickException;

    /**
     * Colourises the image with a pen colour.
     *
     * @param opacity string percentage value for opacity
     * @param target a colour value
     * @exception MagickException on error
     */
    public native MagickImage
	colorizeImage(String opacity, PixelPacket target)
	throws MagickException;

    /**
     * Composite the image supplied onto itself at the specified offsets.
     * @see <a href="http://www.imagemagick.org/script/command-line-options.php#compose">Command line explanation</a>
     * @see <a href="http://www.imagemagick.org/api/composite.php">The underlying ImageMagick call</a>
     * @exception MagickException on error
     */
    public native boolean compositeImage(int compOp,
					 MagickImage compImage,
					 int xOff,
					 int yOff)
	throws MagickException;

    /**
     * Enhances the intensity differences between the lighter and
     * darker elements of the image.
     * @return a boolean value to indicate success
     * @exception MagickException on error
     */
    public native boolean contrastImage(boolean sharpen)
	throws MagickException;

    /**
     * Returns a copy of all fields of the input image.
     * The the pixel memory is allocated but the pixel data is copy
     * is optional.
     * @return a cloned image
     * @exception MagickException on error
     */
    public native MagickImage cloneImage(int columns, int rows,
					 boolean clonePixels)
	throws MagickException;

    /**
     * Create a new image of 8-bit component of the specified dimensions.
     *
     * @param width the width of the new image
     * @param height the height of the new image
     * @param map the components of a pixel
     * @param pixels the raw image in an array of pixels
     * @see <a href="http://www.imagemagick.org/api/constitute.php#ConstituteImage">The underlying ImageMagick call</a>
     * @exception MagickException on error
     */
    public native void constituteImage(int width, int height,
				       String map, byte[] pixels)
	throws MagickException;

    /**
     * Create a new image of 32-bit component of the specified dimensions.
     *
     * @param width the width of the new image
     * @param height the height of the new image
     * @param map the components of a pixel
     * @param pixels the raw image in an array of pixels
     * @see <a href="http://www.imagemagick.org/api/constitute.php#ConstituteImage">The underlying ImageMagick call</a>
     * @exception MagickException on error
     */
    public native void constituteImage(int width, int height,
				       String map, int[] pixels)
	throws MagickException;

    /**
     * Create a new image of float component of the specified dimensions.
     *
     * @param width the width of the new image
     * @param height the height of the new image
     * @param map the components of a pixel
     * @param pixels the raw image in an array of pixels
     * @see <a href="http://www.imagemagick.org/api/constitute.php#ConstituteImage">The underlying ImageMagick call</a>
     * @exception MagickException on error
     */
    public native void constituteImage(int width, int height,
				       String map, float[] pixels)
	throws MagickException;

    /**
     * Creates a new image that is a subregion of the original.
     *
     * @param chopInfo the subimage
     * @return a subimage of the original
     * @exception MagickException on error
     */
    public native MagickImage cropImage(Rectangle chopInfo)
	throws MagickException;

    /**
     * Cycles the image colormap by a specified amount.
     * @exception MagickException on error
     */
    public native void cycleColormapImage(int amount)
	throws MagickException;

    /**
     * Called by finalize to deallocate the image handle.
     */
    public native void destroyImages();

    /**
     * Draws a primitive (line, rectangle, ellipse) on the image.
     * @return a boolean value to indicate success
     * @exception MagickException on error
     */
    public native boolean drawImage(DrawInfo aInfo)
	throws MagickException;

    /**
     * Finds edges in an image. Radius defines the radius of the convolution
     * filter. Use a radius of 0 and Edge() selects a suitable radius for you.
     *
     * @param raduis The radius of the pixel neighborhood.
     *
     * @return A new image with the edges hilighted.
     * @exception MagickException on error
     */
    public native MagickImage edgeImage(double raduis)
	throws MagickException;

    /**
     * Returns a grayscale image with a three-dimensional effect.
     * We convolve the image with a Gaussian operator of the given radius
     * and standard deviation (sigma). For reasonable results, radius
     * should be larger than sigma. Use a radius of 0 and Emboss() selects
     * a suitable radius for you.
     *
     * @param raduis The radius of the pixel neighborhood.
     * @param sigma The standard deviation of the Gaussian, in pixels
     *
     * @return A new, embossed, image.
     * @exception MagickException on error
     */
    public native MagickImage embossImage(double raduis, double sigma)
	throws MagickException;

    /**
     * Applies a digital filter that improves the quality of a noisy image.
     *
     * @return A new, enhanced, image.
     * @exception MagickException on error
     */
    public native MagickImage enhanceImage()
	throws MagickException;

    /**
     *  Performs histogram equalization.
     * @return a boolean value to indicate success
     * @exception MagickException on error
     */
    public native boolean equalizeImage()
	throws MagickException;

    /**
     * Creates a new image that reflects each scanline
     * in the vertical direction.
     * @return a new image that has been flipped
     * @exception MagickException on error
     */
    public native MagickImage flipImage()
	throws MagickException;

    /**
     * Creates a new image that reflects each scanline in the
     * horizontal direction
     * @return a new image that has been flopped
     * @exception MagickException on error
     */
    public native MagickImage flopImage()
	throws MagickException;

    /**
     * Converts the reference image to gamma corrected colors.
     * @return a boolean value to indicate success
     * @exception MagickException on error
     */
    public native boolean gammaImage(String gamma)
	throws MagickException;

    /**
     * Blurs the image using a gaussian operator. The effectiveness of the
     * operator - and the amount of blurring - is controlled by selecting
     * a 'radius' and a 'sigma'. The radius sets the circle around each
     * pixel of the 'neighborhood' used for calculating an average pixel
     * color. Sigma determines how much the calculated average affects the
     * pixel.
     *
     * @param raduis The radius of the Gaussian, in pixels, not counting
     *               the center pixel
     * @param sigma The standard deviation of the Gaussian, in pixels.
     *
     * @return A new, blurred, image.
     * @exception MagickException on error
     */
    public native MagickImage gaussianBlurImage(double raduis, double sigma)
	throws MagickException;

    /**
     * Implodes the image's pixels about the center.
     *
     * @param amount Amount of implosion if positive, explosion if negative.
     *
     * @return A new, imploded, image.
     * @exception MagickException on error
     */
    public native MagickImage implodeImage(double amount)
	throws MagickException;

    /**
     * Returns True if the image is grayscale otherwise False is returned.
     * @return a boolean value to indicate success
     * @exception MagickException on error
     */
    public native boolean isGrayImage()
	throws MagickException;

    /**
     * Returns True if the image is monochrome otherwise False is returned.
     * @return a boolean value to indicate success
     * @exception MagickException on error
     */
    public native boolean isMonochromeImage()
	throws MagickException;

    /**
     * Creates a new image that is a integral size greater
     * than an existing one.
     *
     * @return a magnified image
     * @exception MagickException on error
     */
    public native MagickImage magnifyImage()
	throws MagickException;

    /**
     * Floodfills the designated area with a matte value.
     * @return a boolean value to indicate success
     * @exception MagickException on error
     */
    public native boolean matteFloodfillImage(PixelPacket target,
					      int matte,
					      int x,
					      int y,
					      int method)
	throws MagickException;

    /**
     * Changes the color value of any pixel that matches target
     * and is an immediate neighbor. If the method FillToBorderMethod
     * is specified, the color value is changed for any neighbor pixel
     * that does not match the bordercolor member of image.
     *
     * By default target must match a particular pixel color exactly.
     *
     * @param drawInfo The draw info
     * @param target The RGB value of the target colour
     * @param x the starting x location of the operation
     * @param y the starting y location of the operation
     * @param method either FloodfillMethod or FilltoBorderMethod
     * @return true or false depending on success or failure respectively
     * @throws MagickException if any error occurs
     * @see magick.PaintMethod
     */
    public native boolean colorFloodfillImage(DrawInfo drawInfo,
                                              PixelPacket target,
                                              int x,
                                              int y,
                                              int method)
        throws MagickException;

    /**
     * Applies a digital filter that improves the quality of a noisy image.
     * Each pixel is replaced by the median in a set of neighboring pixels
     * as defined by radius.
     *
     * @param radius The radius of the pixel neighborhood.
     *
     * @return A new, filtered, image.
     * @exception MagickException on error
     */
    public native MagickImage medianFilterImage(double radius)
	throws MagickException;

    /**
     * Creates a new image that is a integral size less than an existing one.
     * @return a minified image
     * @exception MagickException on error
     */
    public native MagickImage minifyImage()
	throws MagickException;

    /**
     * Modulates the hue, saturation, and brightness of an image.
     * @return a boolean value to indicate success
     * @exception MagickException on error
     */
    public native boolean modulateImage(String modulate)
	throws MagickException;

    /**
     * Negates the colors in the reference image. The Grayscale
     * option means that only grayscale values within the image are negated.
     * @return a boolean value to indicate success
     * @exception MagickException on error
     */
    public native boolean negateImage(int grayscale)
	throws MagickException;

    /**
     * Normalizes the pixel values to span the full range of color values.
     * This is a contrast enhancement technique.
     * @return a boolean value to indicate success
     * @exception MagickException on error
     */
    public native boolean normalizeImage()
	throws MagickException;

    /**
     * Applies a special effect filter that simulates an oil painting.
     * Each pixel is replaced by the most frequent color occurring in a
     * circular region defined by radius.
     *
     * @param radius The radius of the pixel neighborhood.
     *
     * @return A new, simulated oil-painting, image.
     * @exception MagickException on error
     */
    public native MagickImage oilPaintImage(double radius)
	throws MagickException;

    /**
     * Changes the color of an opaque pixel to the pen color.
     * @param target the color to search for in the image
     * @param penColor the color to replace it with
     * @return a boolean value to indicate success
     * @exception MagickException on error
     */
    public native boolean opaqueImage(PixelPacket target, PixelPacket penColor)
	throws MagickException;

    /**
     * This operation attempts to reduce the 'noise' in the image. This
     * can be used to eliminate minor dust and scratches from scanned
     * images.
     *<p>
     * The principal function of the noise peak elimination filter is to
     * smooth the objects within an image without losing edge information
     * and without creating undesired structures. The central idea of the
     * algorithm is to replace a pixel with its next neighbor in value in
     * a circular neighborhood if this pixel has been found to be noise. A
     * pixel is defined as noise if the pixel is a minimum or maximum
     * within the neighborhood.
     *
     * @param radius The radius of the pixel neighborhood.
     *
     * @return A new, filtered, image.
     * @exception MagickException on error
     */
    public native MagickImage reduceNoiseImage(double radius)
	throws MagickException;

    /**
     * Converts the reference image from RGB to an alternate colorspace.
     * The transformation matrices are not the standard ones: the weights
     * are rescaled to normalized the range of the transformed values to
     * be [0..MaxRGB].
     * @param colorspace the target colorspace to transform to
     * @return a boolean value to indicate success
     * @exception MagickException on error
     */
    public native boolean rgbTransformImage(int colorspace)
	throws MagickException;

    /**
     * Rolls an image vertically and horizontally.
     * @param xOffset An integer that specifies the number of columns \
                      to roll in the horizontal direction
     * @param yOffset An integer that specifies the number of rows to \
                      roll in the vertical direction
     * @return the rolled image
     * @exception MagickException on error
     */
    public native MagickImage rollImage(int xOffset, int yOffset)
	throws MagickException;

    /**
     * Creates a new image that is a scaled size of an existing one
     * using pixel sampling.
     * @param cols An integer that specifies the number of columns in \
                   the sampled image
     * @param rows An integer that specifies the number of rows in the \
                   sampled image
     * @return the sampled image
     * @exception MagickException on error
     */
    public native MagickImage sampleImage(int cols, int rows)
	throws MagickException;

    /**
     * Return a new image that is a scaled version of the
     * original. To scale a scanline from x pixels to y pixels, each new
     * pixel represents x/y old pixels. To read x/y pixels, read
     * (x/y rounded up) pixels but only count the required fraction of
     * the last old pixel read in your new pixel. The remainder of the
     * old pixel will be counted in the next new pixel.
     * @param cols An integer that specifies the number of columns in \
                   the scaled image
     * @param rows An integer that specifies the number of rows in the \
                   scaled image
     * @return the scaled image
     * @exception MagickException on error
     */
    public native MagickImage scaleImage(int cols, int rows)
	throws MagickException;

    /**
     * Segment an image by analyzing the histograms of the color components
     * and identifying units that are homogeneous using the fuzzy c-means
     * technique.
     *
     * @param colorspace A {@link ColorspaceType} value that indicates the
     *                   colorspace. Empirical evidence suggests that
     *                   distances in YUV or YIQ correspond to perceptual
     *                   color differences more closely than do distances
     *                   in RGB space. The image is then returned to RGB
     *                   colorspace after color reduction.
     * @param cluster_threshold Specify cluster threshold as the number of
     *                   pixels in each cluster must exceed the the
     *                   cluster threshold to be considered valid.
     * @param smoothing_threshold Smoothing threshold eliminates noise in
     *                   the second derivative of the histogram. As the
     *                   value is increased, you can expect a smoother
     *                   second derivative. The default is 1.5.
     *
     * @return The actual number of colors allocated in the colormap.
     * @exception MagickException on error
     * @see ColorspaceType
     */
    public native int segmentImage(int colorspace, double cluster_threshold,
                                                   double smoothing_threshold)
	throws MagickException;

    /**
     * Applies a special effect to the image, similar to the effect achieved
     * in a photo darkroom by selectively exposing areas of photo sensitive
     * paper to light.
     *
     * @param threshold Ranges from 0 to MaxRGB and is a measure of the
     *                  extent of the solarization.
     *
     * @exception MagickException on error
     */
    public native void solarizeImage(double threshold)
	throws MagickException;

    /**
     * Sorts the colormap of a PseudoClass image by decreasing
     * color intensity.
     * @return a boolean value indicating success
     * @exception MagickException on error
     */
    public native boolean sortColormapByIntensity()
	throws MagickException;

    /**
     * A special effects method that randomly displaces each pixel in a
     * block defined by the radius parameter.
     *
     * @param radius Choose a random pixel in a neighborhood of this extent.
     *
     * @return A new, spread, image.
     * @exception MagickException on error
     */
    public native MagickImage spreadImage(int radius)
	throws MagickException;

    /**
     * Swirls the pixels about the center of the image, where degrees
     * indicates the sweep of the arc through which each pixel is moved.
     * You get a more dramatic effect as the degrees move from 1 to 360.
     *
     * @param degrees Defines the tightness of the swirling effect.
     *
     * @return A new, swirled, image.
     * @exception MagickException on error
     */
    public native MagickImage swirlImage(double degress)
	throws MagickException;

    /**
     * Initializes the red, green, and blue intensities of each
     * pixel as defined by the colormap index.
     * @exception MagickException on error
     */
    public native void syncImage()
      throws MagickException;

    /**
     * Layers a texture onto the background of an image.
     * @param image the image to use for texture
     * @exception MagickException on error
     */
    public native void textureImage(MagickImage image)
      throws MagickException;

    /**
     * Thresholds the reference image.
     * @param threshold the threshold value
     * @return a boolean value indicating success
     * @exception MagickException on error
     */
    public native boolean thresholdImage(double threshold)
      throws MagickException;

    /**
     * Creates a new image that is a transformed size of of
     * existing one as specified by the crop and image geometries.
     *
     * If a crop geometry is specified a subregion of the image is
     * obtained. If the specified image size, as defined by the image
     * and scale geometries, is smaller than the actual image size, the
     * image is first minified to an integral of the specified image
     * size with an antialias digital filter. The image is then scaled to
     * the exact specified image size with pixel replication. If the
     * specified image size is greater than the actual image size, the
     * image is first enlarged to an integral of the specified image size
     * with bilinear interpolation. The image is then scaled to the exact
     * specified image size with pixel replication.
     *
     * @param cropGeometry a crop geometry string. This geometry \
                           defines a subregion of the image.
     * @param imageGeometry a image geometry string. The specified \
                            width and height of this geometry string
                            are absolute.
     * @exception MagickException on error
     */
    public native void transformImage(String cropGeometry,
				      String imageGeometry)
      throws MagickException;

    /**
     * Converts the reference image from an alternate colorspace.
     * The transformation matrices are not the standard ones:
     * the weights are rescaled to normalized the range of the
     * transformed values to be [0..MaxRGB].
     *
     * @param colorspace An unsigned integer value defines which \
                         colorspace to transform the image to
     * @return a boolean value indicating success
     * @exception MagickException on error
     */
    public native boolean transformRgbImage(int colorspace)
      throws MagickException;

    /**
     * Creates a matte image associated with the image.
     * @param color The color to search for in the image
     * @param opacity The opacity of the transparent image
     * @return a boolean value indicating success
     * @exception MagickException on error
     */
    public native boolean transparentImage(PixelPacket color, int opacity)
      throws MagickException;

    /**
     * Creates a new image that is a copy of an existing one with
     * the pixels sharpened using an "unsharp" masking technique.
     *<p>
     * This process starts by building a temporary, {@link
     * #gaussianBlurImage blurred}, copy of the image. Then each
     * pixel in this "unsharp" image is compared
     * against its corresponding pixel in the original image. If
     * their difference is above a threshold, a percentage of the
     * difference is added back into the original pixel.
     *<p>
     * The first two arguments, <tt>radius</tt> and <tt>sigma</tt>,
     * specify the blurring used to create the "unsharp" image. See
     * {@link #gaussianBlurImage} for a detail explanation. It will
     * suffice to say that the larger the radius and sigma the more
     * this blurred image will diverge from the original.
     *<p>
     * The last two arguments, <tt>threshold</tt> and <tt>amount</tt>,
     * specify the difference threshold required to apply an adjustment
     * to each pixel and, once the threshold is reached, the amount of
     * the difference to be added back into the original pixels. A high
     * threshold will cause the algorithm to only adjust edge pixels.
     * Specifying a threshold will adjust every pixel.
     *
     * @param raduis    The radius of the gaussian, in pixels, not counting
                        the center pixel
     * @param sigma     The standard deviation of the gaussian, in pixels
     * @param amount    The percentage of the difference between the original
     *                  and the blur image that is added back into the original.
     * @param threshold The threshold in pixels needed to apply the diffence
     *                  amount.
     *
     * @return A sharpened image.
     *
     * @exception MagickException on error
     */
    public native MagickImage unsharpMaskImage(double raduis, double sigma,
                                               double amount, double threshold)
	throws MagickException;

    /**
     * Creates a "ripple" effect in the image by shifting the pixels
     * vertically along a sine wave whose amplitude and wavelength is
     * specified by the given parameters.
     *
     * @param amplitude  Define the amplitude   of the sine wave.
     * @param wavelength Define the wave-length of the sine wave.
     *
     * @return A new, "waved", image.
     * @exception MagickException on error
     */
    public native MagickImage waveImage(double amplitude, double wavelength)
	throws MagickException;

    /**
     * Creates a new image that is a scaled size of an existing one.
     * @return the zoomed image
     * @exception MagickException on error
     */
    public native MagickImage zoomImage(int cols, int rows)
      throws MagickException;

    /**
     * Get the pixels as 8-bit components from the image.
     *
     * @param x x coordinate of the origin of the subimage
     * @param y y coordinate of the origin of the subimage
     * @param width width of the subimage
     * @param height height of the subimage
     * @param map component order of the pixels
     * @param pixels pixels of the subimage
     * @return a boolean value indicating success
     * @exception MagickException on error
     */
    public native boolean dispatchImage(int x, int y, int width, int height,
				    String map, byte[] pixels)
	throws MagickException;

    /**
     * Get the pixels as 32-bit components from the image.
     *
     * @param x x coordinate of the origin of the subimage
     * @param y y coordinate of the origin of the subimage
     * @param width width of the subimage
     * @param height height of the subimage
     * @param map component order of the pixels
     * @param pixels pixels of the subimage
     * @return a boolean value indicating success
     * @exception MagickException on error
     */
    public native boolean dispatchImage(int x, int y, int width, int height,
				    String map, int[] pixels)
	throws MagickException;

    /**
     * Get the pixels as float components from the image.
     *
     * @param x x coordinate of the origin of the subimage
     * @param y y coordinate of the origin of the subimage
     * @param width width of the subimage
     * @param height height of the subimage
     * @param map component order of the pixels
     * @param pixels pixels of the subimage
     * @return a boolean value indicating success
     * @exception MagickException on error
     */
    public native boolean dispatchImage(int x, int y, int width, int height,
					String map, float[] pixels)
	throws MagickException;


    /**
     * Return the image format (i.e., Gif, Jpeg,...)
     *
     * @return the string representing the image format
     * @exception MagickException on error
     * @author Abdulbaset Gaddah <agaddah@yahoo.com>
     */
    public native String getMagick()
	throws MagickException;
    public String getImageFormat()
        throws MagickException
    {
        return getMagick();
    }

    /*
     * Set the image format (i.e., Gif, Jpeg,...).
     *
     * @param imageFormat new image format
     * @exception MagickException on error
     * @author Abdulbaset Gaddah <agaddah@yahoo.com>
     */
    public native void setMagick(String imageFormat)
	throws MagickException;
    public void setImageFormat(String imageFormat)
        throws MagickException
    {
        setMagick(imageFormat);
    }

    /**
     * Return the number of unique colors in an image.
     * @return the number of unique colors
     * @exception MagickException on error
     * @author Abdulbaset Gaddah <agaddah@yahoo.com>
     */
    public native int getNumberColors()
	throws MagickException;

    /*
     * Set the number of unigue colors in an image.
     *
     * @param numberColors new number of unigue colors in an image
     * @exception MagickException on error
     * @author Abdulbaset Gaddah <agaddah@yahoo.com>
     */
    public native void setNumberColors(int numberColors)
	throws MagickException;

    /**
     * Returns True if the Gif image is Animated otherwise False is returned.
     *
     * @return a boolean value representing the animated status of the image
     * @exception MagickException on error
     * @author Abdulbaset Gaddah <agaddah@yahoo.com>
     */
    public native boolean isAnimatedImage()
	throws MagickException;

    /**
     * Creates a new image that is a rotated copy of an existing one.
     * Positive angles rotate counter-clockwise (right-hand rule), while
     * negative angles rotate clockwise. Rotated images are usually larger
     * than the originals and have 'empty' triangular corners. X axis.
     * Empty triangles left over from shearing the image are filled with
     * the color defined by the pixel at location (0,0).
     *
     * @param degrees angle of rotation.
     * @return A image that is a rotation of self
     * @exception MagickException on error
     */
    public native MagickImage rotateImage(double degrees)
	throws MagickException;

    /**
     * Creates a new image that is a shear_image copy of an existing one.
     * Shearing slides one edge of an image along the X or Y axis, creating
     * a parallelogram. An X direction shear slides an edge along the X axis,
     * while a Y direction shear slides an edge along the Y axis. The amount
     * of the shear is controlled by a shear angle. For X direction shears,
     * x_shear is measured relative to the Y axis, and similarly, for Y
     * direction shears y_shear is measured relative to the X axis. Empty
     * triangles left over from shearing the image are filled with the color
     * defined by the pixel at location (0,0).
     *
     * @param x_shear x direction shear amount
     * @param y_shear y direction shear amount
     * @return a sheared image constructor from self.
     * @exception MagickException on error
     */
    public native MagickImage shearImage(double x_shear, double y_shear)
	throws MagickException;


    /**
     * Analyzes the colors within a reference image and chooses a
     * fixed number of colors to represent the image. The goal of
     * the algorithm is to minimize the difference between the input
     * and output image while minimizing the processing time.
     *
     * @param quantizeInfo contains parameters for quantization
     * @return a boolean value indicating success of the process
     * @exception MagickException on error
     */
    public native boolean quantizeImage(QuantizeInfo quantizeInfo)
	throws MagickException;


    /**
     * Convert any colored image to grayscale.
     *
     * @deprecated Use QuantizeInfo with MagickImage.quantizeImage
     *             to acheive the same effect.
     * @exception MagickException on error
     */
    public void setGrayscale()
	throws MagickException
    {
	QuantizeInfo quantizeInfo = new QuantizeInfo();
	quantizeInfo.setColorspace(ColorspaceType.GRAYColorspace);
	quantizeInfo.setNumberColors(256);
	quantizeInfo.setTreeDepth(8);
	quantizeImage(quantizeInfo);
    }

    /**
     * Get the colorspace of the image.
     *
     * @return the colorspace as defined in ColorspaceType
     * @see ColorspaceType
     * @exception MagickException on error
     */
    public native int getColorspace()
        throws MagickException;

    /**
     * Creates a new image that is a copy of an existing one with the
     * pixels sharpened.
     *
     * @param raduis The radius of the gaussian, in pixels, not counting \
                     the center pixel
     * @param sigma The standard deviation of the gaussian, in pixels
     *
     * @return a sharpened image.
     * @exception MagickException on error
     */
    public native MagickImage sharpenImage(double raduis, double sigma)
	throws MagickException;

    /**
     * Creates a new image that is a copy of an existing one with the
     * speckle noise minified. It uses the eight hull algorithm described
     * in Applied Optics, Vol. 24, No. 10, 15 May 1985, ``Geometric filter
     * for Speckle Reduction'', by Thomas R Crimmins. Each pixel in the
     * image is replaced by one of its eight of its surrounding pixels
     * using a polarity and negative hull function.
     *
     * @return a despeckled image
     * @exception MagickException on error
     */
    public native MagickImage despeckleImage()
	throws MagickException;

    /**
     * Applies a general image convolution kernel to an image returns
     * the results. ConvolveImage allocates the memory necessary for
     * the new Image structure and returns a pointer to the new image.
     *
     * @param order The number of columns and rows in the filter kernel.
     * @param kernel An array of double representing the convolution kernel
     *
     * @return a convoled image
     * @exception MagickException on error
     */
    public native MagickImage convolveImage(int order, double[] kernel)
	throws MagickException;

    /**
     * Searches the list of image attributes and returns
     *  the value of the attribute if it exists otherwise null.
     *
     * @param key the key of the attribute
     * @return the value of the attribute if exists, otherwise, null.
     * @exception MagickException on error
     */
    public native String getImageAttribute(String key)
	throws MagickException;

    /**
     * Searches the list of image attributes and replaces the
     * attribute value.  If it is not found in the list, the attribute name
     * and value is added to the list. SetImageAttribute returns True if the
     * attribute is successfully replaced or added to the list, otherwise
     * False. If the value is null, the matching key is deleted from the list.
     *
     * @param key the key of the attribute
     * @param value the value of the attribute
     * @return true if the attribute is replace or false if added
     * @exception MagickException on error
     */
    public native boolean setImageAttribute(String key, String value)
	throws MagickException;

    /**
     * Takes from memory an image in a known format and read it into
     * itself.
     *
     * @param imageInfo a ImageInfo instance
     * @param blob memory containing an image in a known format
     * @exception MagickException on error
     */
    public native void blobToImage(ImageInfo imageInfo, byte[] blob)
	throws MagickException;

    /**
     * Returns an array that contents the image format.
     *
     * @param imageInfo the magick member of this object determines
     *                  output format
     * @return a byte array containing the image in the specified format
     * @exception MagickException on error
     */
    public native byte[] imageToBlob(ImageInfo imageInfo);

    /**
     * Set the units attribute of the image.
     *
     * @param resolutionType the resolution type as defined in ResolutionType
     * @see ResolutionType
     * @exception MagickException on error
     */
    public native void setUnits(int resolutionType)
      throws MagickException;

    /**
     * Get the units attribute of the image.
     *
     * @return A integer representing the resolution type as defined
     *         in ResolutionType
     * @see ResolutionType
     * @exception MagickException on error
     */
    public native int getUnits()
      throws MagickException;

    /**
     * Set the x_resolution attribute in the image.
     *
     * @param xRes x_resolution value
     * @exception MagickException on error
     */
    public native void setXResolution(double xRes)
        throws MagickException;

    /**
     * Get the x_resolution attribute in the image.
     *
     * @return x_resolution value
     * @exception MagickException on error
     */
    public native double getXResolution()
        throws MagickException;

    /**
     * Get the y_resolution attribute in the image.
     *
     * @param yRes y_resolution value
     * @exception MagickException on error
     */
    public native void setYResolution(double yRes)
        throws MagickException;

    /**
     * Get the y_resolution attribute in the image.
     *
     * @return y_resolution value
     * @exception MagickException on error
     */
    public native double getYResolution()
      throws MagickException;

    /**
     * Return image object for next image in sequence of frames.
     * Also sets the next image pointer to NULL.
     *
     * @return next image or null if end of list.
     * @exception MagickException on error
     */
    protected native MagickImage nextImage()
        throws MagickException;

    /**
     * Check if the image has multiple frames.
     *
     * @return true if the image has multiple frames, false, otherwise.
     * @exception MagickException on error
     */
    public native boolean hasFrames()
        throws MagickException;

    /*
     * Count the number of frames in image.
     *
     * @return number of frame in image
     * @exception MagickException on error
     */
    public native int getNumFrames()
        throws MagickException;

    /**
     * Destructively create array of image frames. Contains this image
     * as the first object and frames in sequence.
     *
     * @return an array of image frame
     * @exception MagickException on error
     */
    public MagickImage[] breakFrames()
        throws MagickException
    {
        int length = getNumFrames();
        MagickImage[] list = new MagickImage[length];
        MagickImage image = this;
        for (int i = 0; i < length && image != null; i++) {
            list[i] = image;
            image = image.nextImage();
        }
        return list;
    }

    /**
     * Set a new color profile for the image.
     * @param profile a new color profile. This parameter cannot be null.
     * Note: The profile.name attribute is ignored
     * @see #profileImage
     * @throws MagickException if an error occurs
     */
    public native void setColorProfile(ProfileInfo profile)
        throws MagickException;

    /**
     * Obtain the color profile from the image.
     * @return the color profile of the image
     * @see #profileImage
     * @throws MagickException if an error occurs
     */
    public native ProfileInfo getColorProfile()
        throws MagickException;


    /**
     * Set a new IPTC profile for the image.
     * @param profile a new IPTC profile. This parameter cannot be null.
     * Note: The profile.name attribute is ignored
     * @see #profileImage
     * @throws MagickException if an error occurs
     */
    public native void setIptcProfile(ProfileInfo profile)
        throws MagickException;

    /**
     * Obtain the IPTC profile from the image.
     * @return the IPTC profile of the image
     * @see #profileImage
     * @throws MagickException if an error occurs
     */
    public native ProfileInfo getIptcProfile()
        throws MagickException;

    /**
     * Return the number of generic profiles.
     * @return number of generic profiles
		 * @Deprecated No longer works (after ImageMagick 5.5.7 ?)
     * @throws MagickException if the profile count cannot be retrieved
     */
    public native int getGenericProfileCount()
        throws MagickException;

    /**
     * Return the generic profile specified by the index.
     * @param i the index of the generic profile to retrieve
     * @return a generic ProfileInfo if found, null otheriwse.
		 * @Deprecated No longer works (after ImageMagick 5.5.7 ?)
     * @throws MagickException if an error occurs
     */
    public native ProfileInfo getGenericProfile(int i)
        throws MagickException;

    /**
     * ProfileImage adds or removes a ICM, IPTC, or generic profile
     * from an image.  If the profile name is defined it is deleted
     * from the image. If a filename is given, one or more profiles
     * are read and added to the image.
     * @param profileName name of profile to add or remove
     * @param profileData contents of the profile
     * @return Returns a true if the profile is successfully added or removed
     * @throws MagickException if an error occurs
     */
    public native boolean profileImage(String profileName, byte[] profileData)
        throws MagickException;



		/**
		 * SetImageProfile() adds a named profile to the image. If a profile with
		 * the same name already exists, it is replaced. This method differs from
		 * the ProfileImage() method in that it does not apply CMS color profiles.
		 * @param profileName the profile name, for example icc, exif, and 8bim (8bim is the Photoshop wrapper for iptc profiles).
		 * @param profileData contents of the profile
		 * @return Returns a true if the profile is successfully set
		 * @author Jacob Nordfalk
		 * @since JMagick 6.3.9
		 * @throws MagickException if an error occurs
		 * @see http://www.imagemagick.org/api/profile.php#SetImageProfile
		 */
		public native boolean setImageProfile(String profileName, byte[] profileData)
				throws MagickException;


		/**
		 * GetImageProfile() gets a profile associated with an image by name.
		 * @param profileName name of profile get
		 * @return contents of the profile
		 * @author Jacob Nordfalk
		 * @since JMagick 6.3.9
		 * @throws MagickException if an error occurs
		 * @see http://www.imagemagick.org/api/profile.php#GetImageProfile
		 */
		public native byte[] getImageProfile(String profileName)
				throws MagickException;



    /**
     * Create a montage of all the images in the list.
     * @param montageInfo parameter used in the creation of the montage
     * @return a montage of all images in the list
     * @throws MagickException if an error occurs
     */
    public native MagickImage montageImages(MontageInfo montageInfo)
        throws MagickException;

    /**
     * The Average() method takes a set of images and
     * averages them together. Each image in the set must
     * have the same width and height.
     * @return an image with the pixel component of each image averaged.
     * @throws MagickException upon errors
     */
    public native MagickImage averageImages()
        throws MagickException;

    /**
     * Adjusts the levels of an image given these points:  black,
     * mid, and white.
     * @param levels String representing the black, mid and white levels
     * @return true if successful, false otherwise.
     */
    public native boolean levelImage(String levels)
        throws MagickException;

    /**
     * Returns the current length of the image file or blob.
     * @return current length of the image file or blob
     */
    public native int sizeBlob()
        throws MagickException;

    /**
     * Set the compression attribute.
     * This will affect a following call to writeImage
     * @see #writeImage
     * @param value a value from CompressionType
     * @see CompressionType
     * @see <a href="http://www.imagemagick.org/script/command-line-options.php#compress">Command line explanation</a>
     * @exception MagickException on error
     */
    public native void setCompression(int value)
        throws MagickException;


   /**
     * Get the CompressionType of the image.
     * @return the compression as defined in CompressionType
     * @exception MagickException on error
     * @see CompressionType
     * @author Susan Dorr <sdorr@contentcube.com>
     */
    public native int getCompression()
        throws MagickException;


    /**
     * Get the image type from the MagickImage
     *
     * @param Image
     * @author Susan Dorr <sdorr@contentcube.com>
     */
    public native int getImageType()
        throws MagickException;


    /**
     * Set the border colour for the method borderImage.
     * @param color the border colour
     * @see #borderImage
     * @exception MagickException on error
     */
    public native void setBorderColor(PixelPacket color)
        throws MagickException;


    /**
     * Get the current border colour used by method borderImage.
     * @return the current border colour
     * @see #borderImage
     * @exception MagickException on error
     */
    public native PixelPacket getBorderColor()
        throws MagickException;

    /**
     * Set the background colour.
     * @param color the background colour
     * @exception MagickException on error
     */
    public native void setBackgroundColor(PixelPacket color)
        throws MagickException;

    /**
     * Get the current background colour.
     * @return the current background colour
     * @exception MagickException on error
     */
    public native PixelPacket getBackgroundColor()
        throws MagickException;

    /**
     * Set the time in 1/100ths of a second (0 to 65535) which must
     * expire before displaying the next image in an animated sequence.
     * This option is useful for regulating the animation of a sequence
     * of GIF images within Netscape.
     * @param delay the time delay in 1/100th of a second
     * @throws MagickException upon error
     */
    public native void setDelay(int delay)
        throws MagickException;

    /**
     * Get the time in 1/100ths of a second (0 to 65535) which must
     * expire before displaying the next image in an animated sequence.
     * This option is useful for regulating the animation of a sequence
     * of GIF images within Netscape.
     * @return the current time delay in 1/100th of a second
     * @throws MagickException upon error
     */
    public native int getDelay()
        throws MagickException;


    /**
     * Set the GIF disposal method. This option is used to control how
     * successive frames are rendered (how the preceding frame is disposed
     * of) when creating a GIF animation.
     * @param dispose the disposal method for GIF animation
     * @throws MagickException upon error
     */
    public native void setDispose(int dispose)
        throws MagickException;


    /**
     * Get the GIF disposal method. This option is used to control how
     * successive frames are rendered (how the preceding frame is disposed
     * of) when creating a GIF animation.
     * @return the current disposal method for GIF animation
     * @throws MagickException upon error
     */
    public native int getDispose()
        throws MagickException;


    /**
     * Set the number of iterations to loop an animation (e.g. Netscape
     * loop extension) for.
     * @param iterations the number of iterations
     * @throws MagickException upon error
     */
    public native void setIterations(int iterations)
        throws MagickException;


    /**
     * Get the number of iterations to loop an animation (e.g. Netscape
     * loop extension) for.
     * @return the current number of iterations
     * @throws MagickException upon error
     */
    public native int getIterations()
        throws MagickException;

    /**
     * The number of colors in the colourmap.
     * @return the current number of colors in the image
     * @see #quantizeImage
     * @throws MagickException upon error
     */
    public native int getColors()
        throws MagickException;


    /**
     * Get the The number of colors in the image after QuantizeImage(),
     * or QuantizeImages().
     * @return the current number of colors in the image
     * @throws MagickException upon error
     */
    public native int getTotalColors()
        throws MagickException;

    /**
     * Get the colour specified by the index.
     * @param index the index for which to return a colour
     * @return the colour of the index
     * @throws MagickException upon error
     */
    public native PixelPacket getColormap(int index)
        throws MagickException;

    /**
     * Get the entire colour map.
     * @return the colour map of the image
     * @throws MagickException upon error
     */
    public native PixelPacket[] getColormap()
        throws MagickException;

    /**
     * Get the colour at the specified row and column
     * @param x the x position of the pixel to fetch
     * @param y the y position of the pixel to fetch
     * @return the colour of the index
     * @throws MagickException upon error
     */
    public native PixelPacket getOnePixel(int x, int y)
        throws MagickException;


    /**
     * Determine signature of image and place signature
     * in the image's attributes.
     * @return true if successful, false, otherwise
     * @exception MagickException on error
     * @author Elizabeth Barham &lt;soggytrousers@yahoo.com&gt;
     */
    public native boolean signatureImage()
        throws MagickException;

    /**
     * @return the quality the image was saved
     * @throws MagickException on error
     */
    public native int getQuality()
        throws MagickException;

    /**
     * Set the intent attribute of the image.
     * @param intent the rendering Intent type as defined in RenderingIntent
     * @see RenderingIntent
     * @exception MagickException on error
     */
    public native void setRenderingIntent(int renderingIntent)
      throws MagickException;

    /**
     * Get the intent attribute of the image.
     * @return A integer representing the rendering Intent type as defined
     *         in RenderingIntent
     * @exception MagickException on error
     */
    public native int getRenderingIntent()
      throws MagickException;

    /**
     * Set the matte attribute of the image.
     * @param matte the matte value
     * @exception MagickException on error
     */
    public native void setMatte(boolean matte)
      throws MagickException;

    /**
     * Get the matte attribute of the image.
     * @return A boolean representing the value of the matte attribute
     * @exception MagickException on error
     */
    public native boolean getMatte()
      throws MagickException;

}
