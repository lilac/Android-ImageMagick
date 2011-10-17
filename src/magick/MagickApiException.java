package magick;

/**
 * Encapsulation of the ImageMagick ExceptionInfo structure as
 * well as the exception that is thrown when an ImageMagick
 * API failed.
 *
 * @author Eric Yeo
 */
public class MagickApiException extends MagickException {

    /**
     * Takes a value in ExceptionType.
     */
    private int severity;

    /**
     * An reason for failure.
     */
    private String reason;

    /**
     * A description of the problem.
     */
    private String description;


    /**
     * Construct an API exception.
     *
     * @param mesg error message
     * @param severity one of the value in ExceptionType
     * @qualifier error qualifier
     */
    private MagickApiException(int severity,
                               String reason,
                               String description)
    {
	super(reason);
	this.severity = severity;
	this.reason = reason;
        this.description = description;
    }

    /*
     * Get the severity of the exception.
     *
     * @return severity of the Exception
     */
    public int getSeverity()
    {
	return severity;
    }

    /*
     * Get the reason of the exception.
     *
     * @return reason of the exception.
     */
    public String getReason()
    {
	return reason;
    }

    /**
     * Get the description of the exception.
     *
     * @return description of the exception.
     */
   public String getDescription()
   {
       return description;
   }

}
