== OSU Click Through Agreement plugin ==
Author: Joe Bondra 

== INTRODUCTION ==
This plugin (at the moment) is designed as an OSU-specific click-through agreement for the u.osu.edu EduBlogs-based service.
The plugin is intended to be used exclusively as a mu-plugin. It will not function properly (or at all) in the regular plugins directory.

This plugin stores an option called "osu_click_through_agreement" in wp_usermeta for each user who agrees to the Terms of Service.

The text for the Terms of Service can be altered by a Super Admin at Network Admin->Dashboard->Settings->OSU Click Through. The Terms of
Service text is stored in wp_sitemeta in the wp_sitemeta table as option "osu_click_through_options" in a serialized array at the
key "agreement_text".

== INSTALLATION ==
1. Place osu-click-through directory in /wp-content/mu-plugins/
2. Move osu-click-through/osu-click-through-mu.php into the /wp-content/mu-plugins/ directory

