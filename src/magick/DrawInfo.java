package magick;

/**
 * Encapsulation of the ImageMagick DrawInfo structure.
 *
 * @author Eric Yeo
 */
public class DrawInfo extends Magick {

    /**
     * DrawInfo handle.
     */
    private long drawInfoHandle = 0;

    /**
     * Constructor. Create a DrawInfo structure from defaults in
     * the ImageInfo structure.
     *
     * @param imageInfo default values for DrawInfo this taken from this
     */
    public DrawInfo(ImageInfo imageInfo)
	throws MagickException
    {
	init(imageInfo);
    }

    /**
     * Initialises the DrawInfo structure by taking some default values
     * fromt the ImageInfo.
     *
     * @param imageInfo the ImageInfo from which some default values are taken
     */
    private native void init(ImageInfo imageInfo)
	throws MagickException;

    /**
     * If the garbabe collector removes us, we had better release
     * the memory we occupy.
     */
    protected void finalize()
    {
	destroyDrawInfo();
    }


    /**
     * Remove the storage associated with DrawInfo.
     */
    private native void destroyDrawInfo();


    /**
     * Set the primitive field in the DrawInfo.
     *
     * @param primitive value of the primitive field
     */
    public native void setPrimitive(String primitive)
	throws MagickException;

    /**
     * Get the primitive field in the DrawInfo.
     *
     * @return value of the primitive field.
     */
    public native String getPrimitive()
	throws MagickException;

    /**
     * Get the text field in the DrawInfo.
     *
     * @return value of the text field.
     */
    public native String getText()
	throws MagickException;

    /**
     * Set the text field in the DrawInfo.
     *
     * @param text value of the text field
     */
    public native void setText(String text)
	throws MagickException;

    /**
     * Get the geometry field in the DrawInfo.
     *
     * @return value of the geometry field.
     */
    public native String getGeometry()
	throws MagickException;

    /**
     * Set the geometry field in the DrawInfo.
     *
     * @param geometry value of the geometry field
     */
    public native void setGeometry(String geometry)
	throws MagickException;

    /**
     * Set the font field in the DrawInfo.
     *
     * @param font value of the font field
     */
    public native void setFont(String font)
	throws MagickException;

    /**
     * Get the font field in the DrawInfo.
     *
     * @return value of the font field.
     */
    public native String getFont()
	throws MagickException;

    /**
     * Set the stroke_antialias attribute in the DrawInfo handle.
     *
     * @param strokeAntialias whether antialiasing is enable
     */
    public native void setStrokeAntialias(boolean strokeAntialias)
	throws MagickException;

    /**
     * Return the stroke_antialias attribute in the DrawInfo handle.
     *
     * @return value of the stroke_antialias attribute in DrawInfo
     */
    public native boolean getStrokeAntialias()
	throws MagickException;

    /**
     * Set the text_antialias attribute in the DrawInfo handle.
     *
     * @param textAntialias whether antialiasing is enable
     */
    public native void setTextAntialias(boolean textAntialias)
	throws MagickException;

    /**
     * Return the text_antialias attribute in the DrawInfo handle.
     *
     * @return value of the text_antialias attribute in DrawInfo
     */
    public native boolean getTextAntialias()
	throws MagickException;

    /**
     * Set the gravity attribute in the DrawInfo handle.
     *
     * @param gravity the new GravityType value
     * @see GravityType
     */
    public native void setGravity(int gravity)
	throws MagickException;

    /**
     * Get the gravity attribute in the DrawInfo handle.
     *
     * @return the value of the gravity attribute in the DrawInfo
     * @see GravityType
     */
    public native int getGravity()
	throws MagickException;

    /**
     * Set the opacity attribute in the DrawInfo handle.
     *
     * @param opacity the new opacity value
     */
		public native void setOpacity(int opacity)
	throws MagickException;

    /**
     * Get the opacity attribute in the DrawInfo handle.
     *
     * @return the value of the opacity attribute in the DrawInfo
     */
    public native int getOpacity()
	throws MagickException;

    /**
     * Set the decorate attribute in the DrawInfo handle.
     *
		 * @param decoration the new DecorationType value
     * @see DecorationType
     */
    public native void setDecorate(int decoration)
	throws MagickException;

    /**
     * Get the decorate attribute in the DrawInfo handle.
     *
     * @return the value of the decorate attribute in the DrawInfo
     * @see DecorationType
     */
    public native int getDecorate()
	throws MagickException;

    /**
     * Set the stroke_width attribute in the DrawInfo handle.
     *
     * @param strokeWidth value of the stroke_width attribute
     */
    public native void setStrokeWidth(double strokeWidth)
	throws MagickException;

    /**
     * Get the stroke_width attribute in the DrawInfo handle.
     *
     * @return the value of the stroke_width attribute in DrawInfo
     */
    public native double getStrokeWidth()
	throws MagickException;

    /**
     * Set the pointsize attribute in the DrawInfo handle.
     *
     * @param pointsize value of the pointsize attribute
     */
    public native void setPointsize(double pointsize)
	throws MagickException;

    /**
     * Get the pointsize attribute in the DrawInfo handle.
     *
     * @return the value of the pointsize attribute in DrawInfo
     */
    public native double getPointsize()
	throws MagickException;

    /**
     * Set the fill attribute in the DrawInfo handle.
     *
     * @param fill new value of the fill attribute
     */
    public native void setFill(PixelPacket fill)
	throws MagickException;

    /**
     * Get the fill attribute in the DrawInfo handle.
     *
     * @return the fill attribute in the DrawInfo handle
     */
    public native PixelPacket getFill()
	throws MagickException;

    /**
     * Set the stroke attribute in the DrawInfo handle.
     *
     * @param stroke new value of the fill attribute
     */
    public native void setStroke(PixelPacket stroke)
	throws MagickException;

    /**
     * Get the stroke attribute in the DrawInfo handle.
     *
     * @return the stroke attribute in the DrawInfo handle
     */
    public native PixelPacket getStroke()
	throws MagickException;

    /**
     * Set the undercolor attribute in the DrawInfo handle.
     *
     * @param underColor new value of the fill attribute
     */
    public native void setUnderColor(PixelPacket underColor)
	throws MagickException;

    /**
     * Get the undercolor attribute in the DrawInfo handle.
     *
     * @return the undercolor attribute in the DrawInfo handle
     */
    public native PixelPacket getUnderColor()
	throws MagickException;

    /**
     * Set the border_color attribute in the DrawInfo handle.
     *
     * @param borderColor new value of the fill attribute
     */
    public native void setBorderColor(PixelPacket borderColor)
	throws MagickException;

    /**
     * Get the border_color attribute in the DrawInfo handle.
     *
     * @return the corber_color attribute in the DrawInfo handle
     */
    public native PixelPacket getBorderColor()
	throws MagickException;

    /**
     * Set the tile image in the DrawInfo.
     * @param image the tile image to set
     * @throws MagickException if any error occurs
     */
    public native void setTile(MagickImage image)
        throws MagickException;

    /**
     * Get the tile image from the DrawInfo.
     * @return a copy of the title image
     * @throws MagickException if any error occurs
     */
    public native MagickImage getTile()
        throws MagickException;

}
