<?php
/*
Plugin Name: OSU Click Through Agreement
Plugin URI: http://u.osu.edu
Description: Forbids blog access until click through agreement is logged in usermeta
Version: 1.0
Author: The Ohio State University
Author URI: http://u.osu.edu
*/

/*  Copyright 2013 The Ohio State University

    This program is free software; you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation; either version 2 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program; if not, write to the Free Software
    Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA
*/

// activate plugin
if ( !class_exists('OSUClickThrough') ) {
	require( 'inc/class/OSUClickThrough.class.inc' );
}
$osu_click_through = new OSUClickThrough();
