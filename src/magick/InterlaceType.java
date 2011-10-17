package magick;

/**
 * Corresponds to the ImageMagick enumerated type of the same name.
 *
 * @author Eric Yeo
 */
public interface InterlaceType {

    public final static int UndefinedInterlace = 0;
    public final static int NoInterlace = 1;
    public final static int LineInterlace = 2;
    public final static int PlaneInterlace = 3;
    public final static int PartitionInterlace = 4;

}
