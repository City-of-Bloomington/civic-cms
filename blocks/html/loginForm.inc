<div id="login" class="interfaceBox">
	<h1>Login</h1>
	<table>
	<tr><th>Already a User?</th>
		<td><form method="post" action="<?php echo BASE_URL; ?>/login/login.php">
			<fieldset><legend>Login</legend>
				<table>
				<tr><td><label for="username">User:</label></td>
					<td><input name="username" id="username" size="10" /></td></tr>
				<tr><td><label for="password">Pass:</label></td>
					<td><input type="password" name="password" id="password" size="10" /></td></tr>
				</table>
				<button type="submit" class="login">Login</button>
			</fieldset>
			</form>
		</td>
	</tr>
	<tr><th>New to the Bloomington Website?</th>
		<td><p>If you want to sign in, you'll need to create an account and register first.</p>
			<p>Creating an account will give you access to subscriptions and personalization features.</p>
			<p><a href="<?php echo BASE_URL; ?>/users/pending/create.php">Create a New Account</a></p>
		</td>
	</tr>
	</table>
</div>
<script type="text/javascript">
	document.getElementById('username').focus();
</script>
