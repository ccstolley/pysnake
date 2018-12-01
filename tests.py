from unittest import TestCase
from snake import to_snake

class ToSnakeTests(TestCase):
    def test_basics(self):
        test_strings = (
            ('foo', 'foo'),
            ('fooBar', 'foo_bar'),
            ('fooBarBaz', 'foo_bar_baz'),
            ('foo-Bar-Baz', 'foo_bar_baz'),
            ('foo-bar-baz', 'foo_bar_baz'),
            ('1foo-bar-baz', '1foo_bar_baz'),
            ('dog1Leg', 'dog1_leg'),
            ('dog_leg', 'dog_leg'),
            ('Dog_Leg', 'dog_leg'),
            ('_dog', '_dog'),
            ('_Dog', '_dog'),
            ('Dog_', 'dog_'),
            ('Dog-', 'dog_'),
            ('1213-1231', '1213_1231'),
            ('DOGLEGSALLday', 'doglegsal_lday'),
            ('doglegsallDAY', 'doglegsall_day'),
            ('whenIHave', 'when_i_have'),
            ('whenIHaveFearsThatImayCeaseToBeBeforeMyPenHasGleanedMyTeemingBrainBeforeHigh-piledBooksInCharacteryHoldLikeRichGarnerTheFullRipenedGrain', 'when_i_have_fears_that_imay_cease_to_be_before_my_pen_has_gleaned_my_teeming_brain_before_high_piled_books_in_charactery_hold_like_rich_garner_the_full_ripened_grain'),
            ('', ''),
            ('-', '_'))
        for test, want in test_strings:
            self.assertEqual(to_snake(test), want)

    def test_type_errors(self):
        with self.assertRaises(TypeError):
            to_snake(None)
        with self.assertRaises(TypeError):
            to_snake(1)
        with self.assertRaises(TypeError):
            to_snake(1.2)
        with self.assertRaises(TypeError):
            to_snake(object())

    def test_string_consistency(self):
        self.assertEqual(type(to_snake('whatTheHeck')), str)
        self.assertEqual(type(to_snake(u'whatTheHeck')), str)

    def test_weird_chars(self):
        self.assertEqual(to_snake(u'what\xc3\xa8TheHeck'), u'what_\xe3\xa8the_heck')

    def test_is_stable(self):
        self.assertEqual(to_snake('one_time_only'), 'one_time_only')
        self.assertEqual(to_snake('may_i_ask'), 'may_i_ask')

