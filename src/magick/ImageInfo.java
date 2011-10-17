package magick;

/**
 * Corresponds to the ImageMagick ImageInfo structure.
 *
 * @author Eric Yeo
 */
public class ImageInfo extends Magick {

		/**
		 * Internal ImageMagick ImageInfo handle.
		 * We use long (64-bits) for portability.
		 */
		private long imageInfoHandle = 0;

		/**
		 * Constructor.
		 */
		public ImageInfo()
	throws MagickException
		{
	init();
		}

		/**
		 * Constructor.
		 *
		 * @param fileName initial value of the file_name attribute
		 */
		public ImageInfo(String fileName)
	throws MagickException
		{
	init();
	setFileName(fileName);
		}

		/**
		 * To release memory on cleanup.
		 */
		protected void finalize()
		{
	destroyImageInfo();
		}

		/**
		 * Initialises the internal native handle.
		 */
		public native void init()
	throws MagickException;

		/**
		 * Set the file name attribute of the handle.
		 *
		 * @param fileName the new file name
		 */
		public native void setFileName(String fileName)
	throws MagickException;

		/**
		 * Associates a value with an image option.
		 * Example: <pre>
		 * ImageInfo info = new ImageInfo(...)
		 * info.setImageOption("quantum:polarity", "min-is-white");
		 * </pre>
		 * This then ensures that our tiffs come out in a way that works with
		 * Microsofts Tiff Viewer.
		 *
		 * @param option the image option
		 * @param value the image option value
		 * @since JMagick 6.4.3 (2008-08-05)
		 */
		public native void setImageOption(String option, String value)
	throws MagickException;

		/**
		 * Return the file name attribute of the handle.
		 */
		public native String getFileName()
	throws MagickException;

		/**
		 * Set the affirm attribute.
		 *
		 * @param affirm new value of affirm
		 */
		public native void setAffirm(boolean affirm)
	throws MagickException;

		/**
		 * Get the affirm attribute.
		 */
		public native boolean getAffirm()
	throws MagickException;

		// Set the subimage attribute.
		public native void setSubimage(int value)
	throws MagickException;

		// Get the subimage attribute.
		public native int getSubimage()
	throws MagickException;

		// Set the subrange attribute.
		public native void setSubrange(int value)
	throws MagickException;

		// Get the subrange attribute.
		public native int getSubrange()
	throws MagickException;

		// Set the server_name attribute.
		public native void setServerName(String name)
	throws MagickException;

		// Get the server_name attribute.
		public native String getServerName()
	throws MagickException;

		// Set the font attribute.
		public native void setFont(String font)
	throws MagickException;

		// Get the font attribute.
		public native String getFont()
	throws MagickException;

		// Set the size attribute.
		public native void setSize(String size)
	throws MagickException;

		// Get the size attribute.
		public native String getSize()
	throws MagickException;

		// Set the tile attribute.
		public native void setTile(String tile)
	throws MagickException;

		// Get the tile attribute.
		public native String getTile()
	throws MagickException;

		// Set the density attribute.
		public native void setDensity(String density)
	throws MagickException;

		// Get the density attribute.
		public native String getDensity()
	throws MagickException;

		// Set the page attribute.
		public native void setPage(String page)
	throws MagickException;

		// Get the page attribute.
		public native String getPage()
	throws MagickException;

		// Set the texture attribute.
		public native void setTexture(String texture)
	throws MagickException;

		// Get the texture attribute.
		public native String getTexture()
	throws MagickException;

		// Set the view attribute.
		public native void setView(String view)
	throws MagickException;

		// Get the view attribute.
		public native String getView()
	throws MagickException;

		// Set the adjoin attribute.
		public native void setAdjoin(int value)
	throws MagickException;

		// Get the adjoin attribute.
		public native int getAdjoin()
	throws MagickException;

		// Set the colorspace attribute.
		public native void setColorspace(int value)
	throws MagickException;

		// Get the colorspace attribute.
		public native int getColorspace()
	throws MagickException;

		// Set the compression attribute.
		public native void setCompression(int value)
	throws MagickException;

		// Get the compression attribute.
		public native int getCompression()
	throws MagickException;

		// Set the dither attribute.
		public native void setDither(int value)
	throws MagickException;

		// Get the dither attribute.
		public native int getDither()
	throws MagickException;

		// Set the antialias attribute.
		public native void setAntialias(int value)
	throws MagickException;

		// Get the antialias attribute.
		public native int getAntialias()
	throws MagickException;

		// Set the interlace attribute.
		public native void setInterlace(int value)
	throws MagickException;

		// Get the interlace attribute.
		public native int getInterlace()
	throws MagickException;

		// Set the monochrome attribute.
		public native void setMonochrome(int value)
	throws MagickException;

		// Get the monochrone attribute.
		public native int getMonochrome()
	throws MagickException;

		// Set the pointsize attribute.
		public native void setPointSize(int value)
	throws MagickException;

		// Get the pointsize attribute.
		public native int getPointSize()
	throws MagickException;

		// Set the quality attribute.
		public native void setQuality(int value)
	throws MagickException;

		// Get the quality attribute.
		public native int getQuality()
	throws MagickException;

	/** Set the verbose attribute.
	 * This makes writeImage print out information about the written image on standard output, like:
	 * <pre>
	 * TIFF Directory at offset 0x0
					 Image Width: 102 Image Length: 68
					 Resolution: 72, 72 pixels/inch
					 Bits/Sample: 8
					 Compression Scheme: None
					 Photometric Interpretation: RGB color
					 FillOrder: msb-to-lsb
					 Document Name: "test/output/black_and_White_In_RGBRGB.tif"
					 Orientation: row 0 top, col 0 lhs
					 Samples/Pixel: 3
					 Rows/Strip: 26
					 Planar Configuration: single image plane
					 ICC Profile: <present>, 560 bytes
					 Software: ImageMagick 6.2.6 10/06/06 Q8 http://www.imagemagick.org
	 * </pre>
				 * <p>
				 * Note: The verbose setting is primarily for use with the utility programs.
				 * it is equivalent to the -verbose option for ImageMagick command line tool.
				 * The delegates subsystem does
				 * observe verbose, which is why setting verbose to true causes some
				 * output when loading a PDF or PS file.
				 * </p>
	 * @see MagickImage#writeImage(ImageInfo)
	 */
	public native void setVerbose(int value) throws MagickException;

	/** Get the verbose attribute. @see #setVerbose(int) */
	public native int getVerbose() throws MagickException;

		/**
		 * Set the preview_type attribute.
		 *
		 * @param value new value of the preview_type attribute
		 */
		public native void setPreviewType(int value)
	throws MagickException;

		/**
		 * Get the preview_type attribute.
		 */
		public native int getPreviewType()
	throws MagickException;

		/**
		 * Set the ping attribute.
		 * Used to get information about an image without having to read the image into memory.
		 * Afterwards you can use readImage to get the width, height, file size in bytes, and the file format of the image, without loading the pixels.
		 * @param value new value of the ping attribute
		 */
		public native void setPing(boolean value)
	throws MagickException;

		/**
		 * Get the ping attribute. @see #setPing(boolean)
		 */
		public native boolean getPing()
	throws MagickException;

		/**
		 * Clean up the memory allocated for the handle
		 */
		private native void destroyImageInfo();

		/**
		 * Set the magick attribute of the handle.
		 *
		 * author: Abdulbaset Gaddah <agaddah@yahoo.com>
		 */
		public native void setMagick(String magick)
	throws MagickException;

		/**
		 * Return the magick attribute of the handle.
		 *
		 * author: Abdulbaset Gaddah <agaddah@yahoo.com>
		 */
		public native String getMagick()
	throws MagickException;

		/**
		 * Set the units attribute of the ImageInfo.
		 *
		 * @param resolutionType the resolution type as defined in ResolutionType
		 * @see ResolutionType
		 * @exception MagickException on error
		 */
		public native void setUnits(int resolutionType)
				throws MagickException;

		/**
		 * Get the units attribute of the ImageInfo.
		 *
		 * @return A integer representing the resolution type as defined
		 *         in ResolutionType
		 * @see ResolutionType
		 * @exception MagickException on error
		 */
		public native int getUnits()
				throws MagickException;



		/**
		 * Set the border colour..
		 * @param color the border colour
		 * @see magick.MagickImage#borderImage
		 * @exception MagickException on error
		 */
		public native void setBorderColor(PixelPacket color)
				throws MagickException;


		/**
		 * Get the current border colour..
		 * @return the current border colour
		 * @see magick.MagickImage#borderImage
		 * @exception MagickException on error
		 */
		public native PixelPacket getBorderColor()
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

}
