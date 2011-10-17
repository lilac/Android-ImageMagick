package magick;

import java.awt.image.ImageProducer;
import java.awt.image.ImageConsumer;
import java.awt.image.DirectColorModel;
import java.awt.Dimension;
import java.util.Vector;
import magick.MagickImage;
import magick.MagickException;


/**
 * This class implements the ImageProducer class.
 * It reads the pixels off a MagickImage and sends
 * the pixels to the specified ImageConsumer.
 *
 * @author Eric Yeo
 */
public class MagickProducer
    extends Magick
    implements ImageProducer {

    /**
     * This keeps a copy of the image.
     */
    private MagickImage image = null;

    private Vector consumers = null;

    /**
     * Constructor.
     *
     * @param image the MagickImage to produce an Image from
     */
    public MagickProducer(MagickImage image)
    {
	this.image = image;
	consumers = new Vector();
    }

    /**
     * This method is used to register an ImageConsumer with the
     * ImageProducer for access to the image data during a later
     * reconstruction of the Image.
     *
     * @param consumer to register with the producer
     */
    public void addConsumer(ImageConsumer consumer)
    {
	if (consumer != null && !consumers.contains(consumer)) {
	    consumers.addElement(consumer);
	}
    }

    /**
     * This method determines if a given ImageConsumer object is
     * currently registered with this ImageProducer as one of its
     * consumers.
     *
     * @param consumer to consumer to register with the producer
     */
    public boolean isConsumer(ImageConsumer consumer)
    {
	return consumers.contains(consumer);
    }

    /**
     * This method removes the given ImageConsumer object from the
     * list of consumers currently registered to receive image data.
     * It is not considered an error to remove a consumer that is
     * not currently registered.
     *
     * @param consumer the consumer to check for registration
     */
    public void removeConsumer(ImageConsumer consumer)
    {
	consumers.removeElement(consumer);
    }

    /**
     * This method both registers the given ImageConsumer object
     * as a consumer and starts an immediate reconstruction of the
     * image data which will then be delivered to this consumer and
     * any other consumer which may have already been registered
     * with the producer.
     *
     * @param consumer to be registered before producing the image
     */
    public void startProduction(ImageConsumer consumer)
    {
	addConsumer(consumer);

	// Get the pixels from the image
	Dimension dim;
	int size;
	byte[] pixels;
	try {
	    dim = image.getDimension();
	    size = dim.width * dim.height;
	    pixels = new byte[size*4];
	    image.dispatchImage(0, 0, dim.width, dim.height, "RGBA", pixels);
	}
	catch(MagickException ex) {
	    for (int i = 0; i < consumers.size(); i++) {
		ImageConsumer aConsumer =
		    (ImageConsumer) consumers.elementAt(i);
		aConsumer.imageComplete(ImageConsumer.IMAGEERROR);
	    }
	    return;
	}

	// Set the pixels in the consumers
	int[] img = new int[size];
	DirectColorModel cmodel =
	    new DirectColorModel(32,
				 255 << 24,
				 255 << 16,
				 255 << 8,
				 255);
	for (int i = 0; i < size; i++) {
	    img[i] =
		((pixels[i*4] & 255) << 24) |
		((pixels[i*4+1] & 255) << 16) |
		((pixels[i*4+2] & 255) << 8) |
                (pixels[i*4+3] & 255);
	}
	for (int i = 0; i < consumers.size(); i++) {
	    ImageConsumer aConsumer =
		(ImageConsumer) consumers.elementAt(i);
	    aConsumer.setHints(ImageConsumer.TOPDOWNLEFTRIGHT|
			      ImageConsumer.COMPLETESCANLINES|
			      ImageConsumer.SINGLEPASS|
			      ImageConsumer.SINGLEFRAME);
	    aConsumer.setDimensions(dim.width, dim.height);
	    aConsumer.setPixels(0, 0, dim.width, dim.height,
				cmodel,
				img,
				0,
				dim.width);
	    aConsumer.imageComplete(ImageConsumer.STATICIMAGEDONE);
	}
    }

    /**
     * This method is used by an ImageConsumer to request that the
     * ImageProducer attempt to resend the image data one more time
     * in TOPDOWNLEFTRIGHT order so that higher quality  conversion
     * algorithms which depend on receiving pixels in order can be
     * used to produce a better output version of the image.
     *
     * @param consumer the consumer to register before producing the image
     */
    public void requestTopDownLeftRightResend(ImageConsumer consumer)
    {
	startProduction(consumer);
    }

}
