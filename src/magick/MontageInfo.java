package magick;

/**
 * Encapsulation of the MontageInfo structure.
 * @author Eric Yeo
 */
public class MontageInfo {

    /**
     * Internal ImageMagick MontageInfo handle.
     * We use long (64-bits) for portability.
     */
    private long montageInfoHandle = 0;


    /**
     * Constructor.
     * @param imageInfo contains initial values for MontageInfo
     * @throws MagickException upon irrecoverable errors
     */
    public MontageInfo(ImageInfo imageInfo)
        throws MagickException
    {
        init(imageInfo);
    }


    /**
     * To release memory on cleanup.
     */
    protected void finalize()
    {
	destroyMontageInfo();
    }

    /**
     * Initialises the MontageInfo structure.
     * @param imageInfo used in the initialisation of MontageInfo
     * @throws MagickException upon irrecoverable errors
     */
    private native void init(ImageInfo imageInfo)
        throws MagickException;

    /**
     * Deallocate the handle used for MontageInfo.
     */
    private native void destroyMontageInfo();

    /**
     * Set the geometry string value.
     * @param str new geometry value
     * @throws MagickException upon irrecoverable errors
     */
    public native void setGeometry(String str)
        throws MagickException;

    /**
     * Get the geometry string value.
     * @return the current geometry value
     * @throws MagickException upon irrecoverable errors
     */
    public native String getGeometry()
        throws MagickException;

    /**
     * Set the tile string value.
     * @param str new tile value
     * @throws MagickException upon irrecoverable errors
     */
    public native void setTile(String str)
        throws MagickException;

    /**
     * Get the tile string value.
     * @return the current tile value
     * @throws MagickException upon irrecoverable errors
     */
    public native String getTile()
        throws MagickException;

    /**
     * Set the title string value.
     * @param str new title value
     * @throws MagickException upon irrecoverable errors
     */
    public native void setTitle(String str)
        throws MagickException;

    /**
     * Get the title string value.
     * @return the current title value
     * @throws MagickException upon irrecoverable errors
     */
    public native String getTitle()
        throws MagickException;

    /**
     * Set the frame string value.
     * @param str new frame value
     * @throws MagickException upon irrecoverable errors
     */
    public native void setFrame(String str)
        throws MagickException;

    /**
     * Get the frame string value.
     * @return the current frame value
     * @throws MagickException upon irrecoverable errors
     */
    public native String getFrame()
        throws MagickException;

    /**
     * Set the texture string value.
     * @param str new texture value
     * @throws MagickException upon irrecoverable errors
     */
    public native void setTexture(String str)
        throws MagickException;

    /**
     * Get the texture string value.
     * @return the current texture value
     * @throws MagickException upon irrecoverable errors
     */
    public native String getTexture()
        throws MagickException;

    /**
     * Set the font string value.
     * @param str new font value
     * @throws MagickException upon irrecoverable errors
     */
    public native void setFont(String str)
        throws MagickException;

    /**
     * Get the font string value.
     * @return the current font value
     * @throws MagickException upon irrecoverable errors
     */
    public native String getFont()
        throws MagickException;

    /**
     * Set the pointsize value.
		 * @param pointsize new pointsize value
     * @throws MagickException upon irrecoverable errors
     */
    public native void setPointSize(double pointsize)
        throws MagickException;

    /**
     * Get the pointsize value.
     * @return the current pointsize value
     * @throws MagickException upon irrecoverable errors
     */
    public native double getPointSize()
        throws MagickException;

    /**
     * Set the border_width value.
		 * @param borderWidth new border_width value
     * @throws MagickException upon irrecoverable errors
     */
    public native void setBorderWidth(int borderWidth)
        throws MagickException;

    /**
     * Get the border_width value.
     * @return the current border_width value
     * @throws MagickException upon irrecoverable errors
     */
    public native int getBorderWidth()
        throws MagickException;

    /**
     * Set the gravity value.
		 * @param gravity new gravity value
     * @throws MagickException upon irrecoverable errors
     * @see GravityType
     */
    public native void setGravity(int gravity)
        throws MagickException;

    /**
     * Get the gravity value.
     * @return the current gravity value
     * @throws MagickException upon irrecoverable errors
     * @see GravityType
     */
    public native int getGravity()
        throws MagickException;

    /**
     * Set the shadow flag.
		 * @param shadow new shadow flag
     * @throws MagickException upon irrecoverable errors
     */
    public native void setShadow(boolean shadow)
        throws MagickException;

    /**
     * Get the shadow flag.
     * @return the current shadow flag
     * @throws MagickException upon irrecoverable errors
     */
    public native boolean getShadow()
        throws MagickException;

    /**
     * Set the fill PixelPacket value.
		 * @param fill new fill PixelPacket value
     * @throws MagickException upon irrecoverable errors
     */
    public native void setFill(PixelPacket fill)
        throws MagickException;

    /**
     * Get the fill PixelPacket value
     * @return the current fill PixelPacket value
     * @throws MagickException upon irrecoverable errors
     */
    public native PixelPacket getFill()
        throws MagickException;


    /**
     * Set the stroke PixelPacket value.
		 * @param stroke new stroke PixelPacket value
     * @throws MagickException upon irrecoverable errors
     */
    public native void setStroke(PixelPacket stroke)
        throws MagickException;

    /**
     * Get the stroke PixelPacket value
     * @return the current stroke PixelPacket value
     * @throws MagickException upon irrecoverable errors
     */
    public native PixelPacket getStroke()
        throws MagickException;

    /**
     * Set the background_color PixelPacket value.
		 * @param backgroundColor new background_color PixelPacket value
     * @throws MagickException upon irrecoverable errors
     */
    public native void setBackgroundColor(PixelPacket backgroundColor)
        throws MagickException;

    /**
     * Get the background_color PixelPacket value
     * @return the current background_color PixelPacket value
     * @throws MagickException upon irrecoverable errors
     */
    public native PixelPacket getBackgroundColor()
        throws MagickException;


    /**
     * Set the border_color PixelPacket value.
		 * @param borderColor new border_color PixelPacket value
     * @throws MagickException upon irrecoverable errors
     */
    public native void setBorderColor(PixelPacket borderColor)
        throws MagickException;

    /**
     * Get the border_color PixelPacket value
     * @return the current border_color PixelPacket value
     * @throws MagickException upon irrecoverable errors
     */
    public native PixelPacket getBorderColor()
        throws MagickException;


    /**
     * Set the matte_color PixelPacket value.
		 * @param matteColor new matte_color PixelPacket value
     * @throws MagickException upon irrecoverable errors
     */
    public native void setMatteColor(PixelPacket matteColor)
        throws MagickException;

    /**
     * Get the matte_color PixelPacket value
     * @return the current matte_color PixelPacket value
     * @throws MagickException upon irrecoverable errors
     */
    public native PixelPacket getMatteColor()
        throws MagickException;


    /**
     * Set the filename value.
		 * @param filename new filename value
     * @throws MagickException upon irrecoverable errors
     */
    public native void setFileName(String filename)
        throws MagickException;

    /**
     * Get the filename value
     * @return the current filename value
     * @throws MagickException upon irrecoverable errors
     */
    public native String getFileName()
        throws MagickException;

}
