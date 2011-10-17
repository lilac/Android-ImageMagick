package magick;

/**
 * Exception class for all encompassing Exception.
 *
 * @see MagickApiException
 * @author Eric Yeo
 */
public class MagickException extends Exception {

    /**
     * Construct an exception with a message.
     *
     * @param mesg message attached to the exception
     */
    public MagickException(String mesg)
    {
	super(mesg);
    }

}
