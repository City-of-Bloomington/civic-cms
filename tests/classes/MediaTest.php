<?php
// Call MediaTest::main() if this source file is executed directly.
if (!defined('PHPUnit_MAIN_METHOD')) {
    define('PHPUnit_MAIN_METHOD', 'MediaTest::main');
}

require_once 'PHPUnit/Framework.php';

require_once APPLICATION_HOME.'/classes/Media.inc';

/**
 * Test class for Media.
 * Generated by PHPUnit on 2007-10-04 at 11:49:10.
 */
class MediaTest extends PHPUnit_Framework_TestCase {
    /**
     * Runs the test methods of this class.
     *
     * @access public
     * @static
     */
    public static function main() {
        require_once 'PHPUnit/TextUI/TestRunner.php';

        $suite  = new PHPUnit_Framework_TestSuite('MediaTest');
        $result = PHPUnit_TextUI_TestRunner::run($suite);
    }

    /**
     * Sets up the fixture, for example, opens a network connection.
     * This method is called before a test is executed.
     *
     * @access protected
     */
    protected function setUp() {
    }

    /**
     * Tears down the fixture, for example, closes a network connection.
     * This method is called after a test is executed.
     *
     * @access protected
     */
    protected function tearDown() {
    }

	/**
	 * Tests calling the constructor using an ID
	 */
	public function testConstructById() {
		$media = new Media(1);
		$this->assertTrue($media->getFilename()!='','Could not load Media by ID');
	}

	/**
	 * Tests calling the constructor using an MD5 hash
	 */
	public function testConstructByMD5() {
		$media = new Media('d44aa9df62b8cc743b3acee0b5413b21');
		$this->assertTrue($media->getId()>0,'Could not load Media by MD5 hash');
	}

	/**
	 * Tests calling the constructor using a filename
	 */
	public function testConstructByFilename() {
		$media = new Media('apartmentrow.pdf');
		$this->assertTrue($media->getId()>0,'Could not load Media by filename');
	}

    /**
     * @todo Implement testGetExtensions().
     */
    public function testGetExtensions() {
        // Remove the following lines when you implement this test.
        $this->markTestIncomplete(
          'This test has not been implemented yet.'
        );
    }

    /**
     * @todo Implement testSave().
     */
    public function testSave() {
        // Remove the following lines when you implement this test.
        $this->markTestIncomplete(
          'This test has not been implemented yet.'
        );
    }

    /**
     * @todo Implement testDelete().
     */
    public function testDelete() {
        // Remove the following lines when you implement this test.
        $this->markTestIncomplete(
          'This test has not been implemented yet.'
        );
    }

    /**
     * @todo Implement testSetFile().
     */
    public function testSetFile() {
        // Remove the following lines when you implement this test.
        $this->markTestIncomplete(
          'This test has not been implemented yet.'
        );
    }

    /**
     * @todo Implement testGetDirectory().
     */
    public function testGetDirectory() {
        // Remove the following lines when you implement this test.
        $this->markTestIncomplete(
          'This test has not been implemented yet.'
        );
    }

    /**
     * @todo Implement testGetInternalFilename().
     */
    public function testGetInternalFilename() {
        // Remove the following lines when you implement this test.
        $this->markTestIncomplete(
          'This test has not been implemented yet.'
        );
    }

    /**
     * @todo Implement testGetExtension().
     */
    public function testGetExtension() {
        // Remove the following lines when you implement this test.
        $this->markTestIncomplete(
          'This test has not been implemented yet.'
        );
    }

    /**
     * @todo Implement testGetURL().
     */
    public function testGetURL() {
        // Remove the following lines when you implement this test.
        $this->markTestIncomplete(
          'This test has not been implemented yet.'
        );
    }

    /**
     * @todo Implement testGetDocuments().
     */
    public function testGetDocuments() {
        // Remove the following lines when you implement this test.
        $this->markTestIncomplete(
          'This test has not been implemented yet.'
        );
    }

    /**
     * @todo Implement testCreateValidFilename().
     */
    public function testCreateValidFilename() {
        // Remove the following lines when you implement this test.
        $this->markTestIncomplete(
          'This test has not been implemented yet.'
        );
    }

    /**
     * @todo Implement testPermitsEditingBy().
     */
    public function testPermitsEditingBy() {
        // Remove the following lines when you implement this test.
        $this->markTestIncomplete(
          'This test has not been implemented yet.'
        );
    }

    /**
     * @todo Implement testGetFilesize().
     */
    public function testGetFilesize() {
        // Remove the following lines when you implement this test.
        $this->markTestIncomplete(
          'This test has not been implemented yet.'
        );
    }

    /**
     * @todo Implement testGetId().
     */
    public function testGetId() {
        // Remove the following lines when you implement this test.
        $this->markTestIncomplete(
          'This test has not been implemented yet.'
        );
    }

    /**
     * @todo Implement testGetFilename().
     */
    public function testGetFilename() {
        // Remove the following lines when you implement this test.
        $this->markTestIncomplete(
          'This test has not been implemented yet.'
        );
    }

    /**
     * @todo Implement testGetMime_type().
     */
    public function testGetMime_type() {
        // Remove the following lines when you implement this test.
        $this->markTestIncomplete(
          'This test has not been implemented yet.'
        );
    }

    /**
     * @todo Implement testGetMedia_type().
     */
    public function testGetMedia_type() {
        // Remove the following lines when you implement this test.
        $this->markTestIncomplete(
          'This test has not been implemented yet.'
        );
    }

    /**
     * @todo Implement testGetType().
     */
    public function testGetType() {
        // Remove the following lines when you implement this test.
        $this->markTestIncomplete(
          'This test has not been implemented yet.'
        );
    }

    /**
     * @todo Implement testGetTitle().
     */
    public function testGetTitle() {
        // Remove the following lines when you implement this test.
        $this->markTestIncomplete(
          'This test has not been implemented yet.'
        );
    }

    /**
     * @todo Implement testGetDescription().
     */
    public function testGetDescription() {
        // Remove the following lines when you implement this test.
        $this->markTestIncomplete(
          'This test has not been implemented yet.'
        );
    }

    /**
     * @todo Implement testGetMd5().
     */
    public function testGetMd5() {
        // Remove the following lines when you implement this test.
        $this->markTestIncomplete(
          'This test has not been implemented yet.'
        );
    }

    /**
     * @todo Implement testGetDepartment_id().
     */
    public function testGetDepartment_id() {
        // Remove the following lines when you implement this test.
        $this->markTestIncomplete(
          'This test has not been implemented yet.'
        );
    }

    /**
     * @todo Implement testGetUploaded().
     */
    public function testGetUploaded() {
        // Remove the following lines when you implement this test.
        $this->markTestIncomplete(
          'This test has not been implemented yet.'
        );
    }

    /**
     * @todo Implement testGetUser_id().
     */
    public function testGetUser_id() {
        // Remove the following lines when you implement this test.
        $this->markTestIncomplete(
          'This test has not been implemented yet.'
        );
    }

    /**
     * @todo Implement testGetUser().
     */
    public function testGetUser() {
        // Remove the following lines when you implement this test.
        $this->markTestIncomplete(
          'This test has not been implemented yet.'
        );
    }

    /**
     * @todo Implement testGetDepartment().
     */
    public function testGetDepartment() {
        // Remove the following lines when you implement this test.
        $this->markTestIncomplete(
          'This test has not been implemented yet.'
        );
    }

    /**
     * @todo Implement testSetTitle().
     */
    public function testSetTitle() {
        // Remove the following lines when you implement this test.
        $this->markTestIncomplete(
          'This test has not been implemented yet.'
        );
    }

    /**
     * @todo Implement testSetDescription().
     */
    public function testSetDescription() {
        // Remove the following lines when you implement this test.
        $this->markTestIncomplete(
          'This test has not been implemented yet.'
        );
    }

    /**
     * @todo Implement testSetDepartment_id().
     */
    public function testSetDepartment_id() {
        // Remove the following lines when you implement this test.
        $this->markTestIncomplete(
          'This test has not been implemented yet.'
        );
    }

    /**
     * @todo Implement testSetUploaded().
     */
    public function testSetUploaded() {
        // Remove the following lines when you implement this test.
        $this->markTestIncomplete(
          'This test has not been implemented yet.'
        );
    }

    /**
     * @todo Implement testSetUploadedBy().
     */
    public function testSetUploadedBy() {
        // Remove the following lines when you implement this test.
        $this->markTestIncomplete(
          'This test has not been implemented yet.'
        );
    }

    /**
     * @todo Implement testSetUser().
     */
    public function testSetUser() {
        // Remove the following lines when you implement this test.
        $this->markTestIncomplete(
          'This test has not been implemented yet.'
        );
    }

    /**
     * @todo Implement testSetDepartment().
     */
    public function testSetDepartment() {
        // Remove the following lines when you implement this test.
        $this->markTestIncomplete(
          'This test has not been implemented yet.'
        );
    }
}

// Call MediaTest::main() if this source file is executed directly.
if (PHPUnit_MAIN_METHOD == 'MediaTest::main') {
    MediaTest::main();
}
?>
