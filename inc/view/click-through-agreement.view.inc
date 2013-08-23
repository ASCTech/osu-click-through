<html>
<head>
<meta charset="utf-8">
<title>Terms of Service | u.osu.edu</title>
<link rel="stylesheet" href="https://www.osu.edu/assets/fonts/webfonts.css">
<link rel="stylesheet" href="<?php echo $tos_css; ?>">
</head>
<body>
<div id="page">
	<div id="header">
		
	</div>
	<div id="main" role="main">
		<?php if ( $display_additional_message ) : ?>
		<div id="additional_message" class="updated"><?php echo $additional_message; ?></div>
		<?php endif; ?>
		<?php echo $agreement_text; ?>
		<form id="agreement_form" method="post">
			<?php wp_nonce_field( 'osu_terms_of_service_agreement' ); ?>
			
			<label for="osu_terms_of_service_agreement">
			<input type="checkbox" id="osu_terms_of_service_agreement" name="osu_terms_of_service[agree]">
			I agree to the Terms of Service.</label>
			
			<?php submit_button( 'Submit' ); ?>
		</form>
	</div>
	<div id="footer">
		
	</div>
</div>
</body>
</html>