package magick;

/**
 * Encapsulation of the MagickInfo structure.
 *
 * @author Susan Dorr
 */
public class MagickInfo extends Magick {

    // Internal handle. Used as pointer to MagickInfo
    // structure in memory. We use long (64-bits) for
    // portibility.
    private long magickInfoHandle = 0;

    /**
     * Constructor.
     */
    public MagickInfo(String name)
	throws MagickException
    {
	init(name);
    }

    /**
     * Automated destructor.
     */

    public void finalize()
    {
	destroyMagickInfo(); 
    }

    /**
     * Initialise the MagickInfo structure.
     */
    public native void init(String name)
	throws MagickException;

    /**
     * Deallocate the MagickInfo structure.
     */
    private native void destroyMagickInfo();


    /**
     * Return the description  attribute of the handle.
     */
    public native String getDescription()
	throws MagickException;
}
