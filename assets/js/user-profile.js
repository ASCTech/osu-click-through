/**
 * user-profile.js
 * 	general scripts for OSU CLick Through Agreement plugin
 * 	to be added on profile.php admin page
 * 	 
 */

(function($) {
	$(init);
	
	function init() {
		$( '.osu-terms-of-service' ).hide();
		$( '.osu-terms-of-service' ).before( '<a href="#" title="" class="osu-terms-of-service-toggle">View Terms of Service</a>' );
		$( '.osu-terms-of-service-toggle' ).click( toggleTOS );
	}
	
	function toggleTOS( e ) {
		e.preventDefault();
		$( '.osu-terms-of-service' ).slideToggle();
		if ( $( this ).text() == 'View Terms of Service' ) {
			$( this ).text( 'Hide Terms of Service' );
		}
		else {
			$( this ).text( 'View Terms of Service' );
		}
	}
	
})(jQuery);
