<div class="wrap">
<?php screen_icon( 'options-general' ); ?>
<h2>OSU Click Through Agreement</h2>
<?php if ( isset( $_GET['updated'] ) ) : ?>
<div id="message" class="updated"><p><?php _e( 'Options saved.' ) ?></p></div>
<?php endif; ?>
<?php if ( isset( $_GET['purged'] ) && $_GET['purged'] == 'true' ) : ?>
<div id="message" class="updated"><p><?php _e( 'Terms of Service records purged.' ) ?></p></div>
<?php endif; ?>
<?php if ( isset( $_GET['purged'] ) && $_GET['purged'] == 'false' ) : ?>
<div id="message" class="error"><p><?php _e( 'An error occurred. Terms of Service records not purged.' ) ?></p></div>
<?php endif; ?>
<h2 class="nav-tab-wrapper">  
    <a href="?page=osu-click-through&tab=main_settings" class="nav-tab <?php echo $active_tab == 'main_settings' ? 'nav-tab-active' : ''; ?>">Main Settings</a>  
    <a href="?page=osu-click-through&tab=purge" class="nav-tab <?php echo $active_tab == 'purge' ? 'nav-tab-active' : ''; ?>">Purge</a>  
</h2>
<?php if ( $active_tab == 'main_settings' ) : ?>
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
<?php endif; ?>
<?php if ( $active_tab == 'purge' ) : ?>
<h3>Purge Records</h3>
<?php if ( !isset( $_GET['confirm'] ) ) : ?>
<p><strong><em>WARNING:</em></strong> This action <strong>cannot</strong> be undone.</p>
<p>
If the Terms of Service change significantly, as to require users to agree to a new set of terms,
the agreement records stored in wp_usermeta must be purged.
</p>
<p>
Doing so will <strong><em>IMMEDIATELY</em></strong> force all users to agree to the new Terms of Service
the next time they access the Admin pages (e.g. Dashboard, Add Post, etc.).
</p>
<p>
<strong><em>NOTE:</em></strong> After purging records you will also immediately have to click through the Terms of Service.
</p>
<form method="post">
	<?php wp_nonce_field( 'osu_click_through_purge_tos_records' ); ?>
	<?php submit_button( 'Purge all Terms of Service records', 'primary', 'osu_click_through_purge_tos_records' ); ?>
</form>
<?php else : ?>
<p>Are you absolutely sure you want to purge all Terms of Service records and force agreement to new Terms of Service?</p>
<form method="post">
	<?php wp_nonce_field( 'osu_click_through_purge_tos_records_confirm' ); ?>
	<?php submit_button( 'Yes. I am sure I want to purge all Terms of Service records.', 'primary', 'osu_click_through_purge_tos_records_confirm' ); ?>
</form>
<?php endif; ?>
<?php endif; ?>
</div>