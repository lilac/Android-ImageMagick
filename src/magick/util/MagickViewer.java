package magick.util;

import java.awt.ScrollPane;

import magick.MagickImage;


/**
 * A display pane that provides a scrollable view port
 * for a MagickImage.
 *
 * @author Eric Yeo
 */
public class MagickViewer extends ScrollPane {
    
    /**
     * This is the component that actually displays the
     * MagickImage.
     */
    MagickCanvas canvas;
    

    /**
     * Constructor.
     */
    public MagickViewer() {
	super(SCROLLBARS_AS_NEEDED);
	canvas = new MagickCanvas();
	add(canvas);
    }
    
    /**
     * Sets the display image.
     *
     * @param image the MagickImage to display.
     */
    public void setImage(MagickImage image) {
	canvas.setImage(image);
    }

};
