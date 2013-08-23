== OSU Click Through Agreement plugin ==
Author: Joe Bondra 

== INTRODUCTION ==
This plugin (at the moment) is designed as an OSU-specific click-through agreement for the u.osu.edu EduBlogs-based service.
The plugin is intended to be used exclusively as a mu-plugin. It will not function properly (or at all) in the regular plugins directory.

This plugin stores an option called "osu_click_through_agreement" in wp_usermeta for each user who agrees to the Terms of Service. This
option is a serialized array which contains an index called "date" which stores the date the user clicked through the agreement. (NOTE:
this date is stored in UTC.)

The text for the Terms of Service can be altered by a Super Admin at Network Admin->Dashboard->Settings->OSU Click Through. The Terms of
Service text is stored in wp_sitemeta in the wp_sitemeta table as option "osu_click_through_options" in a serialized array at the
key "agreement_text".

== INSTALLATION ==
1. Place osu-click-through directory in /wp-content/mu-plugins/
2. Move osu-click-through/osu-click-through-mu.php into the /wp-content/mu-plugins/ directory

== UNINSTALL ==
1. To remove records from wp_usermeta, run the purge function at Network Admin->Settings->OSU Click Through->Purge.
2. If any records remain, delete all entries in wp_usermeta with meta_key = "osu_click_through_agreement".
3. Delete the options in wp_sitemeta with option_name "osu_click_through_options"

== INSTRUCTIONS, ETC. ==
1. Default Terms of Service are stored in a variable ($default_agreement_text) in inc/misc/default-agreement-text.inc. (These exist simply to
have something there immediately when the plugin is activated.)
2. Terms of Service can be altered at Network Admin->Dashboard->Settings->OSU Click Through
3. Terms can be purged by using button under the Purge tab on Network Admin->Dashboard->Settings->OSU Click Through
4. Date at which any user has accepted the terms is on the users profile or edit profile page
5. A dashboard widget will be made available on each user's dashboard which displays the current Terms of Service. It can be removed with 
the Screen Options tab by any user.
6. Styles for the Terms of Service page are located in assets/css/tos.css.
7. After purging the Terms of Service, all users will immediately have to agree to the Terms of Service again. This includes
YOU. So, right after clicking through the purge function you will be presented with the Terms of Service page.

