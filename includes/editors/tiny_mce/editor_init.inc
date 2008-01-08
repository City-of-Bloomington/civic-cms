<?php
/**
 * @copyright Copyright (C) 2007 City of Bloomington, Indiana. All rights reserved.
 * @license http://www.gnu.org/copyleft/gpl.html GNU/GPL, see LICENSE.txt
 * @author Cliff Ingham <inghamn@bloomington.in.gov>
 * @param string $content
 * @param string $content_field_name
 */
?>
<script type="text/javascript" src="<?php echo BASE_URL; ?>/editors/tiny_mce/tiny_mce.js"></script>
<script type="text/javascript">
	tinyMCE.init(
	{
		mode : "exact",
		elements : "<?php echo $content_field_name; ?>",

		//apply_source_formatting : true,
		remove_linebreaks: true,
		cleanup_on_startup : true,
		doctype : '<!DOCTYPE html PUBLIC "-//W3C//DTD XHTML 1.1//EN" "http://www.w3.org/TR/xhtml11/DTD/xhtml11.dtd">',
		//encoding : 'xml',
		entity_encoding : 'raw',
		convert_fonts_to_spans : false,
		fix_list_elements : true,
		fix_table_elements : true,
		fix_content_duplication : true,
		//forced_root_block : 'p',
		inline_styles : true,
		remove_trailing_nbsp : true,

		//relative_urls : false,
		//remove_script_host : true,
		//document_base_url : "/",

		//file_browser_callback : 'mediaBrowser',

		theme : "advanced",
		content_css : "<?php echo BASE_URL; ?>/skins/<?php echo $_SESSION['skin']; ?>/skin.css",
		theme_advanced_blockformats : "p,h2,h3,h4,h5,h6,div,blockquote,dt,dd,code,pre",
		theme_advanced_toolbar_location : "top",
		theme_advanced_toolbar_align : "left",
		plugins : 'table,paste',
		theme_advanced_buttons1 : "bold,italic,underline,|,sub,sup,|,bullist,numlist,|,hr,removeformat,formatselect",
		theme_advanced_buttons2 : "cut,copy,paste,|,pastetext,pasteword,selectall,|,undo,redo,|,code,cleanup,help",
		theme_advanced_buttons3 : "",
		theme_advanced_buttons4 : "",

		valid_elements : "" +
		"-strong/-b," +
		"-em/-i," +
		"-strike," +
		"-u," +
		"-p[class|style]," +
		"br," +
		"img[id|longdesc|usemap|class|src|alt=|title|hspace|vspace|width|height|align]," +
		"-sub," +
		"-sup," +
		"-blockquote," +
		"-table[width|height|class|align|summary|class|style]," +
		"-tr[abbr|align|class|rowspan|id|valign|class|style]," +
		"tbody," +
		"thead," +
		"tfoot," +
		"-td[class|colspan|style]," +
		"-th[class|colspan|style|rowspan|width|height|align|valign|scope]," +
		"caption[class|style]," +
		"-div[id|class|style]," +
		"-span[class|style]," +
		"-pre," +
		"address," +
		"-h2," +
		"-h3," +
		"-h4," +
		"-h5," +
		"-h6," +
		"hr," +
		"-ol[class|style]," +
		"-ul[class|style]," +
		"-li[class|style]," +
		"dd[class|style]," +
		"dl[class|style]," +
		"dt[class|style]" +
		"form[action|class|enctype|id|method<get?post|onsubmit]," +
		"fieldset,legend," +
		"label[class|for|id|style]," +
		"input[checked<checked|class|style|id|maxlength|name|size|type<button?checkbox?file?hidden?image?password?radio?reset?submit?text]," +
		"select[multiple<multiple|name|onchange]," +
		"option[value]," +
		"optgroup," +
		"textarea[class|style|cols|id|name|rows]," +
		"button[accesskey|class|style|id|name|onclick|type|value],"
	}
	);
</script>
<textarea name="<?php echo $content_field_name; ?>" id="<?php echo $content_field_name; ?>" rows="40" cols="80"><?php echo $content ?></textarea>
