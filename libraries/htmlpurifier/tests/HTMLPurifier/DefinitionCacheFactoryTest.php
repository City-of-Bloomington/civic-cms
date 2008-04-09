<?php

require_once 'HTMLPurifier/DefinitionCacheFactory.php';

class HTMLPurifier_DefinitionCacheFactoryTest extends HTMLPurifier_Harness
{
    
    protected $factory;
    protected $oldFactory;
    
    function setup() {
        parent::setup();
        $this->factory = new HTMLPurifier_DefinitionCacheFactory();
        $this->oldFactory = HTMLPurifier_DefinitionCacheFactory::instance();
        HTMLPurifier_DefinitionCacheFactory::instance($this->factory);
    }
    
    function teardown() {
        HTMLPurifier_DefinitionCacheFactory::instance($this->oldFactory);
    }
    
    function test_create() {
        $cache = $this->factory->create('Test', $this->config);
        $this->assertEqual($cache, new HTMLPurifier_DefinitionCache_Serializer('Test'));
    }
    
    function test_create_withDecorator() {
        $this->factory->addDecorator('Memory');
        $cache = $this->factory->create('Test', $this->config);
        $cache_real = new HTMLPurifier_DefinitionCache_Decorator_Memory();
        $cache_real = $cache_real->decorate(new HTMLPurifier_DefinitionCache_Serializer('Test'));
        $this->assertEqual($cache, $cache_real);
    }
    
    function test_create_withDecoratorObject() {
        $this->factory->addDecorator(new HTMLPurifier_DefinitionCache_Decorator_Memory());
        $cache = $this->factory->create('Test', $this->config);
        $cache_real = new HTMLPurifier_DefinitionCache_Decorator_Memory();
        $cache_real = $cache_real->decorate(new HTMLPurifier_DefinitionCache_Serializer('Test'));
        $this->assertEqual($cache, $cache_real);
    }
    
    function test_create_recycling() {
        $cache  = $this->factory->create('Test', $this->config);
        $cache2 = $this->factory->create('Test', $this->config);
        $this->assertReference($cache, $cache2);
    }
    
    function test_create_invalid() {
        $this->config->set('Core', 'DefinitionCache', 'Invalid');
        $this->expectError('Unrecognized DefinitionCache Invalid, using Serializer instead');
        $cache = $this->factory->create('Test', $this->config);
        $this->assertIsA($cache, 'HTMLPurifier_DefinitionCache_Serializer');
    }
    
    function test_null() {
        $this->config->set('Core', 'DefinitionCache', null);
        $cache = $this->factory->create('Test', $this->config);
        $this->assertEqual($cache, new HTMLPurifier_DefinitionCache_Null('Test'));
    }
    
    function test_register() {
        generate_mock_once('HTMLPurifier_DefinitionCache');
        $this->config->set('Core', 'DefinitionCache', 'TestCache');
        $this->factory->register('TestCache', $class = 'HTMLPurifier_DefinitionCacheMock');
        $cache = $this->factory->create('Test', $this->config);
        $this->assertIsA($cache, $class);
    }
    
}
