package magick;

/**
 * Used in MagickImage.createImage to specify the size 
 * of component.
 *
 * @author Eric Yeo
 */
public interface TimerState {

    public final int UndefinedTimerState = 0;
    public final int StoppedTimerState = 1;
    public final int RunningTimerState = 2;

}
