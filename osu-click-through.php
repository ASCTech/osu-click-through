<?php
/**
 * osu-click-through.php
 * 	sets up OSU Click Through Plugin
 */

// constants
define( 'OSU_CLICK_THROUGH_BASENAME', basename( dirname(__FILE__) ) );
define( 'OSU_CLICK_THROUGH_DIR', dirname(__FILE__) );
define( 'OSU_CLICK_THROUGH_URL', WPMU_PLUGIN_URL . '/' . OSU_CLICK_THROUGH_BASENAME );

// activate plugin
if ( !class_exists('OSUClickThrough') ) {
	require( 'inc/class/OSUClickThrough.class.inc' );
}
$osu_click_through = new OSUClickThrough();
