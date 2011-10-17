package magick;

/**
 * Class encapsulating some profile related to a image.
 * This class corresponds to the ProfileInfo structure in
 * the C API. ProfileInfo is currently used in the Image
 * structure to store the ICC and IPTC profiles.
 * @deprecated This class is only needed for the old (ImageMagick 5.5.7 ?)
 * methods get/setColorProfile() and get/setIptcProfile().
 * Recommended is to use the new generic methods getImageProfile() and
 * setImageProfile() instead
 * @see MagickImage#setColorProfile
 * @author Eric Yeo &lt;ttey@yeo.nu&gt;
 */
public class ProfileInfo {

    /**
     * Name of the profile.
     */
    String name = null;

    /**
     * Profile information.
     */
    byte[] info = null;

    /**
     * Constructor.
     */
    public ProfileInfo()
    {
    }

    /**
     * Constructor.
     * @param name name of the profile
     * @param info the profile information
     */
    public ProfileInfo(String name, byte[] info)
    {
        this.name = name;
        this.info = info;
    }

    /**
     * Get the profile name.
		 * @Deprecated After ImageMagick 5.5.7 (?) names are not available
     * @return the profile name
     */
    public String getName()
    {
        return name;
    }

    /**
     * Set the profile name.
     */
    public void setName(String name)
    {
        this.name = name;
    }

    /**
     * Get the profile info.
     * @return the profile info
     */
    public byte[] getInfo()
    {
        return info;
    }

    /**
     * Set the profile info.
     */
    public void setInfo(byte[] info)
    {
        this.info = info;
    }

}
