/*
 *  AXWebConstants.h
 *  HIServices
 *
 *  Copyright (c) 2025 Apple Inc. All rights reserved.
 *
 */

#ifndef __AXWEBCONSTANTS__
#define __AXWEBCONSTANTS__

/*! @header AXWebConstants.h
    @discussion
    Accessibility roles, attributes, actions, notifications, and parameterized
    attributes that are specific to web content.

    A significant portion of this header defines the text marker API: a set of
    attributes that custom web browser engines and other rich-text engines
    implement to expose fine-grained text positions to assistive technologies
    such as VoiceOver, Speak Selection, and Hover Text. A text marker is an
    opaque cursor that points to a specific location in a document. Together
    with text marker ranges, text markers let assistive technologies navigate
    by character, word, line, sentence, and paragraph; read selected text;
    describe styling at a position; and convert between geometric points and
    document positions.

    A text marker is an opaque payload: your engine creates one with
    AXTextMarkerCreate, hands it to an assistive technology as the value of
    an attribute, and gets it back unchanged as the parameter to a
    parameterized attribute. Assistive technologies treat markers as black
    boxes; only your engine knows what's inside, leaving you free to encode
    whatever information you need to identify a precise position. The buffer
    is typically a small payload such as a numeric character index, or a
    packed struct identifying a node and an offset within that node.

    Whenever an attribute in this header refers to a character index or a
    number of characters, the unit is a UTF-16 code unit — the same unit
    NSString length and NSAttributedString indices use.

    The AXTextMarkerRef and AXTextMarkerRangeRef types and their C
    constructor and accessor functions live in <code>&lt;HIServices/AXTextMarker.h&gt;</code>.

    For a complete adoption guide, see "Accessibility text markers" in the
    Accessibility framework documentation.
*/

/*——————————————————————————————————————————————————————————————————————————————————————*/
/* Attributes                                                                           */
/*——————————————————————————————————————————————————————————————————————————————————————*/

// CFBooleanRef
#define kAXARIAAtomicAttribute CFSTR("AXARIAAtomic")

// CFNumberRef, 1-based
#define kAXARIAColumnCountAttribute CFSTR("AXARIAColumnCount")

// CFNumberRef, 1-based
#define kAXARIAColumnIndexAttribute CFSTR("AXARIAColumnIndex")

// CFStringRef
#define kAXARIACurrentAttribute CFSTR("AXARIACurrent")

// CFStringRef
#define kAXARIALiveAttribute CFSTR("AXARIALive")

// CFNumberRef, 1-based
#define kAXARIAPosInSetAttribute CFSTR("AXARIAPosInSet")

// CFStringRef
#define kAXARIARelevantAttribute CFSTR("AXARIARelevant")

// CFNumberRef, 1-based
#define kAXARIARowCountAttribute CFSTR("AXARIARowCount")

// CFNumberRef, 1-based
#define kAXARIARowIndexAttribute CFSTR("AXARIARowIndex")

// CFNumberRef, 1-based
#define kAXARIASetSizeAttribute CFSTR("AXARIASetSize")

// CFStringRef
#define kAXAccessKeyAttribute CFSTR("AXAccessKey")

// AXUIElementRef
#define kAXActiveElementAttribute CFSTR("AXActiveElement")

// CFStringRef
#define kAXBrailleLabelAttribute CFSTR("AXBrailleLabel")

// CFStringRef
#define kAXBrailleRoleDescriptionAttribute CFSTR("AXBrailleRoleDescription")

// CFBooleanRef
#define kAXCaretBrowsingEnabledAttribute CFSTR("AXCaretBrowsingEnabled")

// CFArrayRef of CFStringRef
#define kAXDOMClassListAttribute CFSTR("AXDOMClassList")

// CFStringRef
#define kAXDOMIdentifierAttribute CFSTR("AXDOMIdentifier")

// CFStringRef
#define kAXDatetimeValueAttribute CFSTR("AXDateTimeValue")

// CFArrayRef of AXUIElementRef
#define kAXDescribedByAttribute CFSTR("AXDescribedBy")

// CFArrayRef of CFStringRef
#define kAXDropEffectsAttribute CFSTR("AXDropEffects")

// AXUIElementRef
#define kAXEditableAncestorAttribute CFSTR("AXEditableAncestor")

// CFBooleanRef
#define kAXElementBusyAttribute CFSTR("AXElementBusy")

// CFArrayRef of AXUIElementRef
#define kAXErrorMessageElementsAttribute CFSTR("AXErrorMessageElements")

// CFBooleanRef
#define kAXExpandedTextValueAttribute CFSTR("AXExpandedTextValue")

// AXUIElementRef
#define kAXFocusableAncestorAttribute CFSTR("AXFocusableAncestor")

// CFBooleanRef
#define kAXGrabbedAttribute CFSTR("AXGrabbed")

// CFBooleanRef
#define kAXHasDocumentRoleAncestorAttribute CFSTR("AXHasDocumentRoleAncestor")

// CFBooleanRef
#define kAXHasPopupAttribute CFSTR("AXHasPopup")

// CFBooleanRef
#define kAXHasWebApplicationAncestorAttribute CFSTR("AXHasWebApplicationAncestor")

// AXUIElementRef
#define kAXHighestEditableAncestorAttribute CFSTR("AXHighestEditableAncestor")

// CFBooleanRef
#define kAXInlineTextAttribute CFSTR("AXInlineText")

// CFRange
#define kAXIntersectionWithSelectionRangeAttribute CFSTR("AXIntersectionWithSelectionRange")

// CFStringRef
#define kAXInvalidAttribute CFSTR("AXInvalid")

// CFStringRef
#define kAXKeyShortcutsAttribute CFSTR("AXKeyShortcutsValue")

// CFArrayRef of AXUIElementRef
#define kAXLinkUIElementsAttribute CFSTR("AXLinkUIElements")

// CFBooleanRef
#define kAXLoadedAttribute CFSTR("AXLoaded")

// CFNumber, double, 0.0 - 1.0
#define kAXLoadingProgressAttribute CFSTR("AXLoadingProgress")

// AXUIElementRef
#define kAXMathBaseAttribute CFSTR("AXMathBase")

// CFStringRef
#define kAXMathFencedCloseAttribute CFSTR("AXMathFencedClose")

// CFStringRef
#define kAXMathFencedOpenAttribute CFSTR("AXMathFencedOpen")

// AXUIElementRef
#define kAXMathFractionDenominatorAttribute CFSTR("AXMathFractionDenominator")

// AXUIElementRef
#define kAXMathFractionNumeratorAttribute CFSTR("AXMathFractionNumerator")

// CFNumberRef
#define kAXMathLineThicknessAttribute CFSTR("AXMathLineThickness")

// AXUIElementRef
#define kAXMathOverAttribute CFSTR("AXMathOver")

// CFArrayRef of CFDictionary
#define kAXMathPostscriptsAttribute CFSTR("AXMathPostscripts")

// CFArrayRef of CFDictionary
#define kAXMathPrescriptsAttribute CFSTR("AXMathPrescripts")

// AXUIElementRef
#define kAXMathRootIndexAttribute CFSTR("AXMathRootIndex")

// CFArrayRef of AXUIElementRef
#define kAXMathRootRadicandAttribute CFSTR("AXMathRootRadicand")

// AXUIElementRef
#define kAXMathSubscriptAttribute CFSTR("AXMathSubscript")

// AXUIElementRef
#define kAXMathSuperscriptAttribute CFSTR("AXMathSuperscript")

// AXUIElementRef
#define kAXMathUnderAttribute CFSTR("AXMathUnder")

// CFArrayRef of AXUIElementRef
#define kAXOwnsAttribute CFSTR("AXOwns")

// CFStringRef
#define kAXPopupValueAttribute CFSTR("AXPopupValue")

// CFBooleanRef
#define kAXPreventKeyboardDOMEventDispatchAttribute CFSTR("AXPreventKeyboardDOMEventDispatch")

// CFBooleanRef
#define kAXValueAutofillAvailableAttribute CFSTR("AXValueAutofillAvailable")

/*——————————————————————————————————————————————————————————————————————————————————————*/
/*! @group Text Marker Attributes
    @discussion
    Document-scoped, non-parameterized text marker attributes. Each one
    returns the same value regardless of which element in the document
    subtree it's called on.
*/
/*——————————————————————————————————————————————————————————————————————————————————————*/

/*!
    @defined kAXStartTextMarkerAttribute

    @abstract
    The position immediately before the first character in the document.

    @attributeblock Value
    AXTextMarkerRef.

    @attributeblock Writable
    No.
*/
#define kAXStartTextMarkerAttribute CFSTR("AXStartTextMarker")

/*!
    @defined kAXEndTextMarkerAttribute

    @abstract
    The position immediately after the last character in the document.

    @attributeblock Value
    AXTextMarkerRef.

    @attributeblock Writable
    No.
*/
#define kAXEndTextMarkerAttribute CFSTR("AXEndTextMarker")

/*!
    @defined kAXSelectedTextMarkerRangeAttribute

    @abstract
    The current selection, or a zero-length range at the caret if there is
    no selection.

    @attributeblock Value
    AXTextMarkerRangeRef.

    @attributeblock Writable
    Yes.

    @discussion
    When an assistive technology writes a value, update the user-visible
    selection (and, where appropriate, scroll it into view) just as you
    would for a user action. This is how VoiceOver moves the system caret
    and follows the user's focus through your document.
*/
#define kAXSelectedTextMarkerRangeAttribute CFSTR("AXSelectedTextMarkerRange")

/*!
    @defined kAXTextInputMarkedTextMarkerRangeAttribute

    @abstract
    The range covering text that's been provisionally inserted by an input
    method but not yet committed.

    @attributeblock Value
    AXTextMarkerRangeRef.

    @attributeblock Writable
    No.

    @discussion
    Return NULL when no marked text is active.
*/
#define kAXTextInputMarkedTextMarkerRangeAttribute CFSTR("AXTextInputMarkedTextMarkerRange")

/*——————————————————————————————————————————————————————————————————————————————————————*/
/* Attributed string keys                                                               */
/*——————————————————————————————————————————————————————————————————————————————————————*/

// CFBooleanRef
#define kAXDidSpellCheckStringAttribute CFSTR("AXDidSpellCheck")

// CFBooleanRef
#define kAXHighlightStringAttribute CFSTR("AXHighlight")

// CFBooleanRef
#define kAXIsSuggestedDeletionStringAttribute CFSTR("AXIsSuggestedDeletion")

// CFBooleanRef
#define kAXIsSuggestedInsertionStringAttribute CFSTR("AXIsSuggestedInsertion")

// CFBooleanRef
#define kAXIsSuggestionStringAttribute CFSTR("AXIsSuggestion")

/*——————————————————————————————————————————————————————————————————————————————————————*/
/* Notifications                                                                        */
/*——————————————————————————————————————————————————————————————————————————————————————*/

#define kAXActiveElementChangedNotification CFSTR("AXActiveElementChanged")
#define kAXCurrentStateChangedNotification CFSTR("AXCurrentStateChanged")
#define kAXExpandedChangedNotification CFSTR("AXExpandedChanged")
#define kAXInvalidStatusChangedNotification CFSTR("AXInvalidStatusChanged")
#define kAXLayoutCompleteNotification CFSTR("AXLayoutComplete")
#define kAXLiveRegionChangedNotification CFSTR("AXLiveRegionChanged")
#define kAXLiveRegionCreatedNotification CFSTR("AXLiveRegionCreated")
#define kAXLoadCompleteNotification CFSTR("AXLoadComplete")

/*——————————————————————————————————————————————————————————————————————————————————————*/
/* Parameterized Attributes                                                             */
/*——————————————————————————————————————————————————————————————————————————————————————*/

// (NSValue *) - (rectValue); param: (NSValue *) - (rectValue)
#define kAXConvertRelativeFrameParameterizedAttribute CFSTR("AXConvertRelativeFrame")

/*——————————————————————————————————————————————————————————————————————————————————————*/
/*! @group Text Marker Element Ranges
    @discussion
    These attributes return a range scoped to a specific element, and are
    how an assistive technology obtains a starting marker for an element
    it has already encountered through tree traversal.
*/
/*——————————————————————————————————————————————————————————————————————————————————————*/

/*!
    @defined kAXTextMarkerRangeForUIElementParameterizedAttribute

    @abstract
    The full range of text represented by an accessibility element.

    @attributeblock Parameter
    AXUIElementRef.

    @attributeblock Value
    AXTextMarkerRangeRef.

    @discussion
    Allows assistive technologies to obtain a range for an arbitrary
    element they encountered — the canonical way to convert from an element
    to its starting and ending markers.
*/
#define kAXTextMarkerRangeForUIElementParameterizedAttribute CFSTR("AXTextMarkerRangeForUIElement")

/*——————————————————————————————————————————————————————————————————————————————————————*/
/*! @group Text Marker Conversions and Validation
*/
/*——————————————————————————————————————————————————————————————————————————————————————*/

/*!
    @defined kAXTextMarkerForIndexParameterizedAttribute

    @abstract
    The marker at the given character index.

    @attributeblock Parameter
    CFNumberRef. A 0-based character index, where 0 is the position
    immediately before the first character of the document.

    @attributeblock Value
    AXTextMarkerRef.
*/
#define kAXTextMarkerForIndexParameterizedAttribute CFSTR("AXTextMarkerForIndex")

/*!
    @defined kAXIndexForTextMarkerParameterizedAttribute

    @abstract
    The 0-based character index of the given marker.

    @attributeblock Parameter
    AXTextMarkerRef.

    @attributeblock Value
    CFNumberRef.

    @discussion
    Potentially expensive: may require a linear scan from the start of the
    document.
*/
#define kAXIndexForTextMarkerParameterizedAttribute CFSTR("AXIndexForTextMarker")

/*!
    @defined kAXTextMarkerForPositionParameterizedAttribute

    @abstract
    The marker at the visual position closest to the given screen-space
    point. Used for hit testing.

    @attributeblock Parameter
    NSValue wrapping a CGPoint in screen-space coordinates.

    @attributeblock Value
    AXTextMarkerRef.
*/
#define kAXTextMarkerForPositionParameterizedAttribute CFSTR("AXTextMarkerForPosition")

/*!
    @defined kAXUIElementForTextMarkerParameterizedAttribute

    @abstract
    The most-specific accessibility element containing the given position.

    @attributeblock Parameter
    AXTextMarkerRef.

    @attributeblock Value
    AXUIElementRef.

    @discussion
    For most documents this will be a leaf such as a static text or
    text-bearing inline element.
*/
#define kAXUIElementForTextMarkerParameterizedAttribute CFSTR("AXUIElementForTextMarker")

/*!
    @defined kAXTextMarkerRangeForUnorderedTextMarkersParameterizedAttribute

    @abstract
    A range whose start is the earlier of two markers in document order
    and whose end is the later.

    @attributeblock Parameter
    CFArrayRef of two AXTextMarkerRefs.

    @attributeblock Value
    AXTextMarkerRangeRef.

    @discussion
    Used by assistive technologies that have two markers from different
    sources (for example the start and end of a selection drag) and need
    to put them in document order. Also forms the basis of semantic
    equivalence: two markers are semantically equivalent if the range
    formed from them, paired with kAXLengthForTextMarkerRangeParameterizedAttribute,
    has zero length, even when their byte buffers differ. Potentially
    expensive: may require a linear scan of the document.
*/
#define kAXTextMarkerRangeForUnorderedTextMarkersParameterizedAttribute CFSTR("AXTextMarkerRangeForUnorderedTextMarkers")

/*!
    @defined kAXTextMarkerIsValidParameterizedAttribute

    @abstract
    Whether the marker still refers to a meaningful position in the
    current document.

    @attributeblock Parameter
    AXTextMarkerRef.

    @attributeblock Value
    CFBooleanRef. kCFBooleanTrue if the marker is still meaningful;
    kCFBooleanFalse otherwise (for example, after the document has been
    reloaded or the node it referenced has been removed from the tree).
*/
#define kAXTextMarkerIsValidParameterizedAttribute CFSTR("AXTextMarkerIsValid")

/*——————————————————————————————————————————————————————————————————————————————————————*/
/*! @group Text Marker Range Queries
*/
/*——————————————————————————————————————————————————————————————————————————————————————*/

/*!
    @defined kAXStringForTextMarkerRangeParameterizedAttribute

    @abstract
    The plain text contained in the range.

    @attributeblock Parameter
    AXTextMarkerRangeRef.

    @attributeblock Value
    CFStringRef.
*/
#define kAXStringForTextMarkerRangeParameterizedAttribute CFSTR("AXStringForTextMarkerRange")

/*!
    @defined kAXAttributedStringForTextMarkerRangeParameterizedAttribute

    @abstract
    The text in the range with style information applied as attributes.

    @attributeblock Parameter
    AXTextMarkerRangeRef.

    @attributeblock Value
    CFAttributedStringRef.

    @discussion
    Style attributes typically include font, foreground color, underline,
    misspelling marks, suggestion ranges, and similar. NSRange locations
    and lengths inside the returned attributed string are UTF-16 code unit
    indices. Attributed string keys should be the accessibility-specific ones
    defined in NSAccessibilityConstants.h, e.g. NSAccessibilityFontTextAttribute,
    NSAccessibilityForegroundColorTextAttribute, and so on.
*/
#define kAXAttributedStringForTextMarkerRangeParameterizedAttribute CFSTR("AXAttributedStringForTextMarkerRange")

/*!
    @defined kAXBoundsForTextMarkerRangeParameterizedAttribute

    @abstract
    The screen-space bounding rectangle of the text in the range.

    @attributeblock Parameter
    AXTextMarkerRangeRef.

    @attributeblock Value
    NSValue wrapping a CGRect.

    @discussion
    For multi-line ranges, return a rectangle that encompasses every line.
*/
#define kAXBoundsForTextMarkerRangeParameterizedAttribute CFSTR("AXBoundsForTextMarkerRange")

/*!
    @defined kAXLengthForTextMarkerRangeParameterizedAttribute

    @abstract
    The number of characters covered by the range, in UTF-16 code units.

    @attributeblock Parameter
    AXTextMarkerRangeRef.

    @attributeblock Value
    CFNumberRef.
*/
#define kAXLengthForTextMarkerRangeParameterizedAttribute CFSTR("AXLengthForTextMarkerRange")

/*——————————————————————————————————————————————————————————————————————————————————————*/
/*! @group Text Marker Character Navigation
*/
/*——————————————————————————————————————————————————————————————————————————————————————*/

/*!
    @defined kAXNextTextMarkerForTextMarkerParameterizedAttribute

    @abstract
    The next character position. Returns NULL at the end of the document.

    @attributeblock Parameter
    AXTextMarkerRef.

    @attributeblock Value
    AXTextMarkerRef.
*/
#define kAXNextTextMarkerForTextMarkerParameterizedAttribute CFSTR("AXNextTextMarkerForTextMarker")

/*!
    @defined kAXPreviousTextMarkerForTextMarkerParameterizedAttribute

    @abstract
    The previous character position. Returns NULL at the start of the
    document.

    @attributeblock Parameter
    AXTextMarkerRef.

    @attributeblock Value
    AXTextMarkerRef.
*/
#define kAXPreviousTextMarkerForTextMarkerParameterizedAttribute CFSTR("AXPreviousTextMarkerForTextMarker")

/*——————————————————————————————————————————————————————————————————————————————————————*/
/*! @group Text Marker Word Navigation
    @discussion
    A word range covers exactly one word, excluding any leading or
    trailing whitespace. Word ranges typically also exclude trailing
    punctuation, though the exact word-segmentation rules — including how
    to handle punctuation within or at the end of a word, language-specific
    tokenization, and non-text or replaced content — are up to your engine.

    The four word attributes split into two pairs that behave differently
    at edge cases.

    The left and right word attributes return the word that the marker is
    on; they never skip past whitespace. The result is an empty range any
    time the marker isn't right next to a word: in a whitespace gap, at
    the start of the document for left word, at the end of the document
    for right word, or anywhere else not adjacent to a word's first or
    last character.

    The next and previous word attributes return a position at the next
    word boundary in the requested direction, skipping any whitespace in
    between. From inside a word, they resolve to the boundary of that
    word. They return NULL if there's no word in the requested direction.
    These are the attributes assistive technologies use to walk through
    a document word-by-word.
*/
/*——————————————————————————————————————————————————————————————————————————————————————*/

/*!
    @defined kAXLeftWordTextMarkerRangeForTextMarkerParameterizedAttribute

    @abstract
    The word the marker is on, looking left: the word containing the
    marker, or the word whose last character is immediately to the left.

    @attributeblock Parameter
    AXTextMarkerRef.

    @attributeblock Value
    AXTextMarkerRangeRef.
*/
#define kAXLeftWordTextMarkerRangeForTextMarkerParameterizedAttribute CFSTR("AXLeftWordTextMarkerRangeForTextMarker")

/*!
    @defined kAXRightWordTextMarkerRangeForTextMarkerParameterizedAttribute

    @abstract
    The word the marker is on, looking right: the word containing the
    marker, or the word whose first character is immediately to the right.

    @attributeblock Parameter
    AXTextMarkerRef.

    @attributeblock Value
    AXTextMarkerRangeRef.
*/
#define kAXRightWordTextMarkerRangeForTextMarkerParameterizedAttribute CFSTR("AXRightWordTextMarkerRangeForTextMarker")

/*!
    @defined kAXNextWordEndTextMarkerForTextMarkerParameterizedAttribute

    @abstract
    The position at the end of the next word forward — the end of the
    word containing the marker if the marker is inside one, otherwise the
    end of the word that follows.

    @attributeblock Parameter
    AXTextMarkerRef.

    @attributeblock Value
    AXTextMarkerRef.
*/
#define kAXNextWordEndTextMarkerForTextMarkerParameterizedAttribute CFSTR("AXNextWordEndTextMarkerForTextMarker")

/*!
    @defined kAXPreviousWordStartTextMarkerForTextMarkerParameterizedAttribute

    @abstract
    The position at the start of the previous word backward — the start
    of the word containing the marker if the marker is inside one,
    otherwise the start of the word that precedes.

    @attributeblock Parameter
    AXTextMarkerRef.

    @attributeblock Value
    AXTextMarkerRef.
*/
#define kAXPreviousWordStartTextMarkerForTextMarkerParameterizedAttribute CFSTR("AXPreviousWordStartTextMarkerForTextMarker")

/*——————————————————————————————————————————————————————————————————————————————————————*/
/*! @group Text Marker Line Navigation
    @discussion
    A line is a single visual row of text after layout, with soft wraps
    treated as line boundaries.
*/
/*——————————————————————————————————————————————————————————————————————————————————————*/

/*!
    @defined kAXLineForTextMarkerParameterizedAttribute

    @abstract
    The 0-based index of the line containing the marker.

    @attributeblock Parameter
    AXTextMarkerRef.

    @attributeblock Value
    CFNumberRef.

    @discussion
    Potentially expensive: may require a linear scan of the document.
*/
#define kAXLineForTextMarkerParameterizedAttribute CFSTR("AXLineForTextMarker")

/*!
    @defined kAXTextMarkerRangeForLineParameterizedAttribute

    @abstract
    The range of the line with the given 0-based index.

    @attributeblock Parameter
    CFNumberRef.

    @attributeblock Value
    AXTextMarkerRangeRef.

    @discussion
    Potentially expensive: may require a linear scan of the document.
*/
#define kAXTextMarkerRangeForLineParameterizedAttribute CFSTR("AXTextMarkerRangeForLine")

/*!
    @defined kAXLineTextMarkerRangeForTextMarkerParameterizedAttribute

    @abstract
    The range of the line containing the marker.

    @attributeblock Parameter
    AXTextMarkerRef.

    @attributeblock Value
    AXTextMarkerRangeRef.
*/
#define kAXLineTextMarkerRangeForTextMarkerParameterizedAttribute CFSTR("AXLineTextMarkerRangeForTextMarker")

/*!
    @defined kAXLeftLineTextMarkerRangeForTextMarkerParameterizedAttribute

    @abstract
    The range of the line at or immediately before the marker.

    @attributeblock Parameter
    AXTextMarkerRef.

    @attributeblock Value
    AXTextMarkerRangeRef.
*/
#define kAXLeftLineTextMarkerRangeForTextMarkerParameterizedAttribute CFSTR("AXLeftLineTextMarkerRangeForTextMarker")

/*!
    @defined kAXRightLineTextMarkerRangeForTextMarkerParameterizedAttribute

    @abstract
    The range of the line at or immediately after the marker.

    @attributeblock Parameter
    AXTextMarkerRef.

    @attributeblock Value
    AXTextMarkerRangeRef.
*/
#define kAXRightLineTextMarkerRangeForTextMarkerParameterizedAttribute CFSTR("AXRightLineTextMarkerRangeForTextMarker")

/*!
    @defined kAXNextLineEndTextMarkerForTextMarkerParameterizedAttribute

    @abstract
    The position at the end of the line containing or following the
    marker.

    @attributeblock Parameter
    AXTextMarkerRef.

    @attributeblock Value
    AXTextMarkerRef.
*/
#define kAXNextLineEndTextMarkerForTextMarkerParameterizedAttribute CFSTR("AXNextLineEndTextMarkerForTextMarker")

/*!
    @defined kAXPreviousLineStartTextMarkerForTextMarkerParameterizedAttribute

    @abstract
    The position at the start of the line containing or preceding the
    marker.

    @attributeblock Parameter
    AXTextMarkerRef.

    @attributeblock Value
    AXTextMarkerRef.
*/
#define kAXPreviousLineStartTextMarkerForTextMarkerParameterizedAttribute CFSTR("AXPreviousLineStartTextMarkerForTextMarker")

/*——————————————————————————————————————————————————————————————————————————————————————*/
/*! @group Text Marker Sentence Navigation
*/
/*——————————————————————————————————————————————————————————————————————————————————————*/

/*!
    @defined kAXSentenceTextMarkerRangeForTextMarkerParameterizedAttribute

    @abstract
    The range of the sentence containing the marker.

    @attributeblock Parameter
    AXTextMarkerRef.

    @attributeblock Value
    AXTextMarkerRangeRef.
*/
#define kAXSentenceTextMarkerRangeForTextMarkerParameterizedAttribute CFSTR("AXSentenceTextMarkerRangeForTextMarker")

/*!
    @defined kAXNextSentenceEndTextMarkerForTextMarkerParameterizedAttribute

    @abstract
    The position at the end of the sentence containing or following the
    marker.

    @attributeblock Parameter
    AXTextMarkerRef.

    @attributeblock Value
    AXTextMarkerRef.
*/
#define kAXNextSentenceEndTextMarkerForTextMarkerParameterizedAttribute CFSTR("AXNextSentenceEndTextMarkerForTextMarker")

/*!
    @defined kAXPreviousSentenceStartTextMarkerForTextMarkerParameterizedAttribute

    @abstract
    The position at the start of the sentence containing or preceding the
    marker.

    @attributeblock Parameter
    AXTextMarkerRef.

    @attributeblock Value
    AXTextMarkerRef.
*/
#define kAXPreviousSentenceStartTextMarkerForTextMarkerParameterizedAttribute CFSTR("AXPreviousSentenceStartTextMarkerForTextMarker")

/*——————————————————————————————————————————————————————————————————————————————————————*/
/*! @group Text Marker Paragraph Navigation
*/
/*——————————————————————————————————————————————————————————————————————————————————————*/

/*!
    @defined kAXParagraphTextMarkerRangeForTextMarkerParameterizedAttribute

    @abstract
    The range of the paragraph containing the marker.

    @attributeblock Parameter
    AXTextMarkerRef.

    @attributeblock Value
    AXTextMarkerRangeRef.
*/
#define kAXParagraphTextMarkerRangeForTextMarkerParameterizedAttribute CFSTR("AXParagraphTextMarkerRangeForTextMarker")

/*!
    @defined kAXNextParagraphEndTextMarkerForTextMarkerParameterizedAttribute

    @abstract
    The position at the end of the paragraph containing or following the
    marker.

    @attributeblock Parameter
    AXTextMarkerRef.

    @attributeblock Value
    AXTextMarkerRef.
*/
#define kAXNextParagraphEndTextMarkerForTextMarkerParameterizedAttribute CFSTR("AXNextParagraphEndTextMarkerForTextMarker")

/*!
    @defined kAXPreviousParagraphStartTextMarkerForTextMarkerParameterizedAttribute

    @abstract
    The position at the start of the paragraph containing or preceding
    the marker.

    @attributeblock Parameter
    AXTextMarkerRef.

    @attributeblock Value
    AXTextMarkerRef.
*/
#define kAXPreviousParagraphStartTextMarkerForTextMarkerParameterizedAttribute CFSTR("AXPreviousParagraphStartTextMarkerForTextMarker")

/*——————————————————————————————————————————————————————————————————————————————————————*/
/*! @group Text Marker Style Navigation
    @discussion
    A style range is a maximal contiguous run of characters that share
    the same visual styling — same font, same foreground color, same
    decorations, and so on. Assistive technologies use this to describe
    stylistic transitions without re-reading the entire attributed string.
*/
/*——————————————————————————————————————————————————————————————————————————————————————*/

/*!
    @defined kAXStyleTextMarkerRangeForTextMarkerParameterizedAttribute

    @abstract
    The largest range surrounding the marker over which the visual
    styling is uniform.

    @attributeblock Parameter
    AXTextMarkerRef.

    @attributeblock Value
    AXTextMarkerRangeRef.
*/
#define kAXStyleTextMarkerRangeForTextMarkerParameterizedAttribute CFSTR("AXStyleTextMarkerRangeForTextMarker")

/*——————————————————————————————————————————————————————————————————————————————————————*/
/* Roles                                                                                */
/*——————————————————————————————————————————————————————————————————————————————————————*/

#define kAXImageMapRole CFSTR("AXImageMap")

/*——————————————————————————————————————————————————————————————————————————————————————*/
/* Subroles                                                                             */
/*——————————————————————————————————————————————————————————————————————————————————————*/

#define kAXApplicationAlertDialogSubrole CFSTR("AXApplicationAlertDialog")
#define kAXApplicationAlertSubrole CFSTR("AXApplicationAlert")
#define kAXApplicationDialogSubrole CFSTR("AXApplicationDialog")
#define kAXApplicationGroupSubrole CFSTR("AXApplicationGroup")
#define kAXApplicationLogSubrole CFSTR("AXApplicationLog")
#define kAXApplicationMarqueeSubrole CFSTR("AXApplicationMarquee")
#define kAXApplicationStatusSubrole CFSTR("AXApplicationStatus")
#define kAXApplicationTimerSubrole CFSTR("AXApplicationTimer")
#define kAXAudioSubrole CFSTR("AXAudio")
#define kAXCodeStyleGroupSubrole CFSTR("AXCodeStyleGroup")
#define kAXDefinitionSubrole CFSTR("AXDefinition")
#define kAXDeleteStyleGroupSubrole CFSTR("AXDeleteStyleGroup")
#define kAXDetailsSubrole CFSTR("AXDetails")
#define kAXDocumentArticleSubrole CFSTR("AXDocumentArticle")
#define kAXDocumentMathSubrole CFSTR("AXDocumentMath")
#define kAXDocumentNoteSubrole CFSTR("AXDocumentNote")
#define kAXEmptyGroupSubrole CFSTR("AXEmptyGroup")
#define kAXFieldsetSubrole CFSTR("AXFieldset")
#define kAXFileUploadButtonSubrole CFSTR("AXFileUploadButton")
#define kAXInsertStyleGroupSubrole CFSTR("AXInsertStyleGroup")
#define kAXLandmarkBannerSubrole CFSTR("AXLandmarkBanner")
#define kAXLandmarkComplementarySubrole CFSTR("AXLandmarkComplementary")
#define kAXLandmarkContentInfoSubrole CFSTR("AXLandmarkContentInfo")
#define kAXLandmarkMainSubrole CFSTR("AXLandmarkMain")
#define kAXLandmarkNavigationSubrole CFSTR("AXLandmarkNavigation")
#define kAXLandmarkRegionSubrole CFSTR("AXLandmarkRegion")
#define kAXLandmarkSearchSubrole CFSTR("AXLandmarkSearch")
#define kAXMathFenceOperatorSubrole CFSTR("AXMathFenceOperator")
#define kAXMathFencedSubrole CFSTR("AXMathFenced")
#define kAXMathFractionSubrole CFSTR("AXMathFraction")
#define kAXMathIdentifierSubrole CFSTR("AXMathIdentifier")
#define kAXMathMultiscriptSubrole CFSTR("AXMathMultiscript")
#define kAXMathNumberSubrole CFSTR("AXMathNumber")
#define kAXMathOperatorSubrole CFSTR("AXMathOperator")
#define kAXMathRootSubrole CFSTR("AXMathRoot")
#define kAXMathRowSubrole CFSTR("AXMathRow")
#define kAXMathSeparatorOperatorSubrole CFSTR("AXMathSeparatorOperator")
#define kAXMathSquareRootSubrole CFSTR("AXMathSquareRoot")
#define kAXMathSubscriptSuperscriptSubrole CFSTR("AXMathSubscriptSuperscript")
#define kAXMathTableCellSubrole CFSTR("AXMathTableCell")
#define kAXMathTableRowSubrole CFSTR("AXMathTableRow")
#define kAXMathTableSubrole CFSTR("AXMathTable")
#define kAXMathTextSubrole CFSTR("AXMathText")
#define kAXMathUnderOverSubrole CFSTR("AXMathUnderOver")
#define kAXMeterSubrole CFSTR("AXMeter")
#define kAXRubyInlineSubrole CFSTR("AXRubyInline")
#define kAXRubyTextSubrole CFSTR("AXRubyText")
#define kAXSubscriptStyleGroupSubrole CFSTR("AXSubscriptStyleGroup")
#define kAXSummarySubrole CFSTR("AXSummary")
#define kAXSuperscriptStyleGroupSubrole CFSTR("AXSuperscriptStyleGroup")
#define kAXTabPanelSubrole CFSTR("AXTabPanel")
#define kAXTermSubrole CFSTR("AXTerm")
#define kAXTimeGroupSubrole CFSTR("AXTimeGroup")
#define kAXUserInterfaceTooltipSubrole CFSTR("AXUserInterfaceTooltip")
#define kAXVideoSubrole CFSTR("AXVideo")
#define kAXWebApplicationSubrole CFSTR("AXWebApplication")

 #endif // __AXWEBCONSTANTS__
