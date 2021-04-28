#include "stringdecoratortests.h"

namespace cm {
namespace data { // Instance

static StringDecoratorTests instance;

StringDecoratorTests::StringDecoratorTests()
    : TestSuite( "IntDecoratorTests" )
{
}

}

namespace data { // Tests

void cm::data::StringDecoratorTests::constructor_givenNoParameters_setsDefaultProperties()
{

}

void StringDecoratorTests::constructor_givenParameters_setsProperties()
{

}

void StringDecoratorTests::setValue_givenNewValue_updatesValueAndEmitsSignal()
{

}

void StringDecoratorTests::setValue_givenSameValue_takesNoAction()
{

}

void StringDecoratorTests::jsonValue_whenDefaultValue_returnsJson()
{

}

void StringDecoratorTests::jsonValue_whenValueSet_returnsJson()
{

}

void StringDecoratorTests::update_whenPresentInJson_updatesValue()
{

}

void StringDecoratorTests::update_whenNotPresentInJson_updatesValueToDefault()
{

}

}}
