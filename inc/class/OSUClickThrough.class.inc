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
		}
		add_action( 'muplugins_loaded', array( $this, 'create_options' ) );
	}
	
	public function create_options() {
		// create options if necessary
		$options = get_site_option( '' );
		
		if( $options === FALSE ) {
			// options do not yet exist, create options
			
			// grab default agreement text (hacky at the moment)
			include( OSU_CLICK_THROUGH_DIR . "/inc/misc/default-agreement-text.inc" );
			
			$options = array(
				'agreement_text' => $default_agreement_text,
			);
			
			add_site_option( 'osu_click_through_options', $options );
		}
	} // end create_options
	
	public function check_user_agreement() {
		$current_user = wp_get_current_user();
		
		// If the meta value does not exist and $single is true the function will return an empty string.
		$user_has_agreed = get_user_meta( $current_user->ID, 'osu_click_through_agreement', TRUE );
		
		if ($user_has_agreed === '' ) {
			// no value exists for user agreement need to display form before proceeding to WordPress
			$options = get_site_option( 'osu_click_through_options' );
			$agreement_text = $options['agreement_text'];
			
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
		
			if ( isset( $_POST['osu_click_through_options']['agreement_text'] ) ) {
				$agreement_text = wp_kses( 
					$_POST['osu_click_through_options']['agreement_text'],
					wp_kses_allowed_html( 'post' )
				);
				
				$options = array(
					'agreement_text' => $agreement_text, 
				);
				
				update_site_option( 'osu_click_through_options', $options );
			}
		
			wp_redirect( add_query_arg( 'updated', 'true', network_admin_url( 'settings.php?page=osu-click-through' ) ) );
			exit();
		}
		
		if ( isset( $_POST['osu_terms_of_service'] ) ) {
			check_admin_referer( 'osu_terms_of_service_agreement' );
			
			if ( isset( $_POST['osu_terms_of_service']['agree'] ) ) {
				$current_user = wp_get_current_user();
				
				update_user_meta( $current_user->ID, 'osu_click_through_agreement', date( 'Y-m-d H:i:s' ) );
				
				$wp_http_referer = $_POST['_wp_http_referer'];
				wp_redirect( $wp_http_referer );
				exit();
			}
		}
	} // end admin_process_post
	
	public function options_page() {
		// check for appropriate access
		if ( ! current_user_can( 'manage_network_options' ) )
			wp_die( __( 'You do not have permission to access this page.' ) );
		
		// get options
		$options = get_site_option( 'osu_click_through_options' );
		$agreement_text = $options['agreement_text'];
		
		// render page
		include( OSU_CLICK_THROUGH_DIR . '/inc/view/options-page.view.inc' );
		
	} // end options_page
	
	private function purge_agreement_usermeta() {
		// TODO: purge all osu_click_through_agreement options from wp_usermeta
	} // end purge_agreement_usermeta
}
