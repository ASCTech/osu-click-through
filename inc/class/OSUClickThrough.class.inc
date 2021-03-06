<?php
/**
 * OSUClickThrough.class.inc
 * 	Defines class OSUClickThrough
 */
 
class OSUClickThrough {
	public function OSUClickThrough() {
		// actions
		if( is_admin() ) {
			add_action( 'admin_init', array( $this, 'admin_process_post' ) );
			add_action( 'admin_init', array( $this, 'check_user_agreement' ) );	
			add_action( 'network_admin_menu', array( $this, 'add_menus' ) );
			add_action( 'admin_enqueue_scripts', array( $this, 'add_admin_scripts' ) );
			add_action( 'wp_dashboard_setup', array( $this, 'add_dashboard_widgets' ) );
		}
		add_action( 'muplugins_loaded', array( $this, 'create_options' ) );
		add_action( 'show_user_profile', array( $this, 'add_agreement_info_to_user_profile' ) );
		add_action( 'edit_user_profile', array( $this, 'add_agreement_info_to_user_profile' ) );
	}
	
	public function create_options() {
		// create options if necessary
		$options = get_site_option( 'osu_click_through_options' );
		
		if( $options === false ) {
			// options do not yet exist, create options
			
			// grab default agreement text (hacky at the moment)
			include( OSU_CLICK_THROUGH_DIR . "/inc/misc/default-agreement-text.inc" );
			
			// grab default additional message (also, hacky at the moment)
			include( OSU_CLICK_THROUGH_DIR . "/inc/misc/default-additional-message.inc" );
			
			$options = array(
				'agreement_text' => $default_agreement_text,
				'additional_message' => $default_additional_message,
				'display_additional_message' => 1,
			);
			
			add_site_option( 'osu_click_through_options', $options );
		}
	} // end create_options
	
	public function check_user_agreement() {
		$current_user = wp_get_current_user();
		
		// If the meta value does not exist and $single is true the function will return an empty string.
		$user_has_agreed = get_user_meta( $current_user->ID, 'osu_click_through_agreement', true );
		
		if ($user_has_agreed === '' ) {
			// no value exists for user agreement need to display form before proceeding to WordPress
			$options = get_site_option( 'osu_click_through_options' );
			$agreement_text = wpautop( wp_kses_stripslashes( $options['agreement_text'] ) );
			$additional_message = wp_kses_stripslashes( $options['additional_message'] );
			$display_additional_message = wp_kses_stripslashes( $options['display_additional_message'] );
			
			$tos_css = OSU_CLICK_THROUGH_URL . '/assets/css/tos.css';
			
			// render form
			include( OSU_CLICK_THROUGH_DIR . '/inc/view/click-through-agreement.view.inc' );
		
			exit();
		}
	} // end check_user_agreement
	
	public function add_menus() {
		add_submenu_page( 'settings.php', 'OSU Click Through Agreement', 'OSU Click Through', 'manage_network_options', 'osu-click-through', array( $this, 'options_page') );
	} // end add_menus
	
	public function admin_process_post() {
		if ( isset( $_POST['osu_click_through_options'] ) && current_user_can( 'manage_network_options' ) ) {
			check_admin_referer( 'osu_click_through_options' );
		
			$new_options = array();
			$current_options = get_site_option( 'osu_click_through_options' );
		
			if ( isset( $_POST['osu_click_through_options']['agreement_text'] ) ) {
				$agreement_text = wp_kses_post( $_POST['osu_click_through_options']['agreement_text'] );
				
				$new_options['agreement_text'] = $agreement_text;
			}
			
			if ( isset( $_POST['osu_click_through_options']['additional_message'] ) ) {
				$additional_message = wp_kses_post( $_POST['osu_click_through_options']['additional_message'] );
				
				$new_options['additional_message'] = $additional_message;
			}
			
			$new_options['display_additional_message'] = isset( $_POST['osu_click_through_options']['display_additional_message'] ) ? 1 : 0;
			
			$options = array_merge( $current_options, $new_options );
			
			update_site_option( 'osu_click_through_options', $options );
			
			$query_args = array(
				'updated' => 'true',
				'tab' => 'main_settings',
			);
		
			wp_redirect( add_query_arg( $query_args, network_admin_url( 'settings.php?page=osu-click-through' ) ) );
			exit();
		}
		
		if ( isset( $_POST['osu_terms_of_service'] ) ) {
			check_admin_referer( 'osu_terms_of_service_agreement' );
			
			if ( isset( $_POST['osu_terms_of_service']['agree'] ) ) {
				$current_user = wp_get_current_user();
				
				// store agreement date in UTC
				$default_timezone = date_default_timezone_get();
				date_default_timezone_set( 'UTC' );
				
				$agreement_info = array(
					'date' => date( 'Y-m-d H:i:s' ),
				);
				
				date_default_timezone_set( $default_timezone );
				
				update_user_meta( $current_user->ID, 'osu_click_through_agreement', $agreement_info );
				
				$wp_http_referer = $_POST['_wp_http_referer'];
				wp_redirect( $wp_http_referer );
				exit();
			}
		}

		if ( isset( $_POST['osu_click_through_purge_tos_records'] ) && current_user_can( 'manage_network_options' ) ) {
			check_admin_referer( 'osu_click_through_purge_tos_records' );
			
			$query_args = array(
				'confirm' => 'true',
				'tab' => 'purge',
			);
			
			wp_redirect( add_query_arg( $query_args, network_admin_url( 'settings.php?page=osu-click-through' ) ) );
			exit();
			
		}
		
		if ( isset( $_POST['osu_click_through_purge_tos_records_confirm'] ) && current_user_can( 'manage_network_options' ) ) {
			check_admin_referer( 'osu_click_through_purge_tos_records_confirm' );
			
			// delete all Terms of Service agreement records from wp_usermeta
			$success = OSUClickThrough::purge_agreement_usermeta();
			
			if ( $success ) {
				$query_args = array(
					'purged' => 'true',
					'tab' => 'purge',
				);
			}
			else {
				$query_args = array(
					'purged' => 'false',
					'tab' => 'purge',
				);
			}
			
			wp_redirect( add_query_arg( $query_args, network_admin_url( 'settings.php?page=osu-click-through' ) ) );
			exit();
			
			
		}
	} // end admin_process_post
	
	public function add_agreement_info_to_user_profile() {
		global $profileuser;
			
		// get variables
		$options = get_site_option( 'osu_click_through_options' );
		$agreement_text = wpautop( wp_kses_stripslashes( $options['agreement_text'] ) );
		
		// will need to drive any headings down a notch...
		$agreement_text = OSUClickThrough::move_headings_down( $agreement_text, 2 );
		
		$agreement_info = get_user_meta( $profileuser->ID, 'osu_click_through_agreement', true );
		$agreement_date = false;
		
		// If the meta value does not exist and $single is true the function will return an empty string.
		if ( !( $agreement_info === '' ) ) {
			// agreement date is stored as UTC
			$default_timezone = date_default_timezone_get();
			date_default_timezone_set( 'UTC' );
			
			$agreement_date = date( 'F j, Y g:i:s a (e)', strtotime( $agreement_info['date'] ) );
			
			date_default_timezone_set( $default_timezone );
		}
		
		// render info
		include( OSU_CLICK_THROUGH_DIR . '/inc/view/user-profile-info.view.inc' );
	}
	
	public function options_page() {
		// check for appropriate access
		if ( ! current_user_can( 'manage_network_options' ) )
			wp_die( __( 'You do not have permission to access this page.' ) );
			
		// get current tab
		$active_tab = isset( $_GET[ 'tab' ] ) ? $_GET[ 'tab' ] : 'main_settings';  
		
		// get options
		$options = get_site_option( 'osu_click_through_options' );
		$agreement_text = wp_kses_stripslashes( $options['agreement_text'] );
		$additional_message = wp_kses_stripslashes( $options['additional_message'] );
		$display_additional_message = wp_kses_stripslashes( $options['display_additional_message'] );
		
		// render page
		include( OSU_CLICK_THROUGH_DIR . '/inc/view/options-page.view.inc' );
		
	} // end options_page
	
	function add_dashboard_widgets() {
		wp_add_dashboard_widget( 'osu_click_through_tos_dashboard_widget', 'U.OSU Terms of Service', array( $this, 'tos_dashboard_widget' ) );
	}
	
	function tos_dashboard_widget() {
		// get agreement text
		$options = get_site_option( 'osu_click_through_options' );
		$agreement_text = wpautop( wp_kses_stripslashes( $options['agreement_text'] ) );
		
		// will need to drive any headings down a notch... widget headings are h3
		$agreement_text = OSUClickThrough::move_headings_down( $agreement_text, 4 );
		
		echo $agreement_text;
	}
	
	function add_admin_scripts( $hook ) {
		if( 
			$hook == 'profile.php' ||
			$hook == 'user-edit.php'
		) {
			wp_enqueue_script( 'osu-click-through-user-profile-js', OSU_CLICK_THROUGH_URL . '/assets/js/user-profile.js', array( 'jquery' ) );
			wp_enqueue_style( 'osu-click-through-user-profile-css', OSU_CLICK_THROUGH_URL . '/assets/css/user-profile.css' );
		}
		wp_enqueue_style( 'osu-click-through-dashboard-widget-css', OSU_CLICK_THROUGH_URL . '/assets/css/dashboard-widget.css' );
	}
	
	
	/**
	 * move_headings_down
	 * 	a convenience function to display terms of service html headings in context (for valid markup)
	 */
	private function move_headings_down( $html_str, $highest_level = 2 ) {
		if ( $highest_level > 6 ) {
			$highest_level = 6;
		}
		
		for( $i = 1; $i <= $highest_level - 1; $i++ ) {
			for( $j = 5; $j >= 1; $j-- )
			{
				$new_level = $j + 1;
				$html_str = str_replace( "<h{$j}>", "<h{$new_level}>", $html_str );
				$html_str = str_replace( "</h{$j}>", "</h{$new_level}>", $html_str );
			}
		}

		return $html_str;
	}
	
	/**
	 * purge_agreement_usermeta
	 * 	purges all entries for stored click through records from wp_usermeta
	 */
	private function purge_agreement_usermeta() {
		// TODO: purge all osu_click_through_agreement options from wp_usermeta
		$success = delete_metadata( 'user', null, 'osu_click_through_agreement', '', true );
		
		return $success;
	} // end purge_agreement_usermeta
}
