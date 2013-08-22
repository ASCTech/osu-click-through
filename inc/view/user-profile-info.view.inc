<div id="osu-click-through-user-profile-addition">
	<h3>Terms of Service Agreement</h3>
	<?php if ( $agreement_date ) : ?>
	<p>
	This user agreed to the U.OSU.EDU Terms of Service on: 
	<span class="osu-click-through-agreement-date"><?php echo $agreement_date; ?></span>
	</p>
	<div class="osu-terms-of-service">
	<?php echo $agreement_text; ?>
	</div>
	<?php else : ?>
	<p>This user has not yet accepted the U.OSU.EDU Terms of Service.</p>
	<?php endif; ?>
</div>

