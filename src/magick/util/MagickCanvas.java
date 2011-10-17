package magick.util;

import java.awt.Canvas;
import java.awt.Image;
import java.awt.Graphics;
import java.awt.image.ImageObserver;
import java.awt.Dimension;
import magick.MagickImage;
import magick.MagickProducer;


/**
 * This class a specialisation of Canvas to display
 * MagickImage in AWT.
 *
 * @author Eric Yeo
 */
public class MagickCanvas extends Canvas {

    /**
     * The AWT version of the image.
     */
    private Image image;

    /**
     * Width of the image.
     */
    private int width;

    /**
     * Height of the image.
     */
    private int height;


    /**
     * Implements the image observer to wait for the
     * image to be completely loaded.
     */
    private class ImageNotification implements ImageObserver {

	/**
	 * This method is called when the image is completely loaded.
	 */
	public boolean imageUpdate(Image img,
				   int infoflags,
				   int x,
				   int y,
				   int w,
				   int h) {
	    width = w;
	    height = h;
	    setSize(w, h);
	    repaint();
	    return false;
	}
	
    }


    /**
     * Set the viewing image.
     *
     * @param magickImage the MagickImage to view
     */
    public void setImage(MagickImage magickImage) {
	image = createImage(new MagickProducer(magickImage));
	ImageNotification notify = new ImageNotification();
	width = image.getWidth(notify);
	height = image.getHeight(notify);
	if (width > 0 && height > 0) {
	    setSize(width, height);
	    repaint();
	}
    }
    

    /**
     * Method to draw the image onto the Canvas.
     *
     * @param g the Graphics object for drawing
     */
    public void paint(Graphics g) {
	if (image != null) {
	    g.drawImage(image, 0, 0, this);
	}
	else {
	    super.paint(g);
	}
    }

    /**
     * Return the preferred size of the Canvas.
     */
    public Dimension getPreferredSize() {
	return new Dimension(width, height);
    }

    /**
     * Constructor.
     */
    public MagickCanvas() {
	image = null;
	width = 0;
	height = 0;
    }
    
}
