<div class="wrap">
<?php screen_icon( 'options-general' ); ?>
<h2>OSU Click Through Agreement</h2>
<?php if ( isset( $_GET['updated'] ) ) : ?>
<div id="message" class="updated"><p><?php _e( 'Options saved.' ) ?></p></div>
<?php endif; ?>
<h3>Main Settings</h3>
<form method="post">
	<?php wp_nonce_field( 'osu_click_through_options' ); ?>
	<table class="form-table">
	<tr valign="top">
		<th scope="row"><label for="agreement_text"><?php _e( 'Agreement Text' ) ?></label></th>
		<td>
		<?php
			wp_editor(
				$agreement_text,
				'agreementtext',
				array(
					'textarea_name' => 'osu_click_through_options[agreement_text]',
					'media_buttons' => FALSE,
					'teeny' => TRUE,
				)
			);
		?>
		</td>
	</tr>
	</table>
		
	<?php submit_button(); ?>
</form>
</div>