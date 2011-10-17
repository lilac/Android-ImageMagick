package magick;

/**
 * Encapsulation of the QuantizedInfo structure.
 *
 * @author Eric Yeo
 */
public class QuantizeInfo extends Magick {

    // Internal handle. Used as pointer to QuantizedInfo
    // structure in memory. We use long (64-bits) for
    // portibility.
    private long quantizeInfoHandle = 0;

    /**
     * Constructor.
     */
    public QuantizeInfo()
	throws MagickException
    {
	init();
    }

    /**
     * Automated destructor.
     */
    protected void finalize()
    {
	destroyQuantizeInfo();
    }

    /**
     * Initialise the QuantizeInfo structure.
     */
    public native void init()
	throws MagickException;

    /**
     * Deallocate the QuantizeInfo structure.
     */
    private native void destroyQuantizeInfo();


    /**
     * Set the value of number_colors field in the QuantizeInfo structure.
     *
     * @param value new value of number_colors
     */
    public native void setNumberColors(int value)
	throws MagickException;


    /**
     * Return the value of number_colors field in the QuantizInfo structure.
     *
     * @return current value of number_colors field
     */
    public native int getNumberColors()
	throws MagickException;


    /**
     * Set the value of tree_depth field in the QuantizeInfo structure.
     *
     * @param value new value of tree_depth
     */
    public native void setTreeDepth(int value)
	throws MagickException;


    /**
     * Return the value of tree_depth field in the QuantizInfo structure.
     *
     * @return current value of tree_depth field
     */
    public native int getTreeDepth()
	throws MagickException;


    /**
     * Set the value of dither field in the QuantizeInfo structure.
     *
     * @param value new value of dither
     */
    public native void setDither(int value)
	throws MagickException;


    /**
     * Return the value of dither field in the QuantizInfo structure.
     *
     * @return current value of dither field
     */
    public native int getDither()
	throws MagickException;


    /**
     * Set the value of colorspace field in the QuantizeInfo structure.
     *
     * @param value new value of colorspace
     * @see ColorspaceType
     */
    public native void setColorspace(int value)
	throws MagickException;


    /**
     * Return the value of color_space field in the QuantizInfo structure.
     *
     * @return current value of color_space field
     */
    public native int getColorspace()
	throws MagickException;


    /**
     * Set the value of measure_error field in the QuantizeInfo structure.
     *
     * @param value new value of measure_error
     */
    public native void setMeasureError(int value)
	throws MagickException;


    /**
     * Return the value of measure_error field in the QuantizInfo structure.
     *
     * @return current value of measure_error field
     */
    public native int getMeasureError()
	throws MagickException;

}
