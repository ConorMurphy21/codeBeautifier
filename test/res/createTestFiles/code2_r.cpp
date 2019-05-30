using namespace Microsoft::Console::Types;
using namespace Microsoft::Console::Render;

HRESULT GdiEngine::InvalidateSystem(const RECT* const prcDirtyClient) noexcept
{
    RETURN_HR(_InvalidCombine(prcDirtyClient));
}

HRESULT GdiEngine::InvalidateScroll(const COORD* const pcoordDelta) noexcept
{
    if (pcoordDelta->X != 0 || pcoordDelta->Y != 0)
    {
        POINT ptDelta = { 0 };
        RETURN_IF_FAILED(_ScaleByFont(pcoordDelta, &ptDelta));

        RETURN_IF_FAILED(_InvalidOffset(&ptDelta));

        SIZE szInvalidScrollNew;
        RETURN_IF_FAILED(LongAdd(_szInvalidScroll.cx, ptDelta.x, &szInvalidScrollNew.cx));
        RETURN_IF_FAILED(LongAdd(_szInvalidScroll.cy, ptDelta.y, &szInvalidScrollNew.cy));

        _szInvalidScroll = szInvalidScrollNew;
    }

    return S_OK;
}

HRESULT GdiEngine::InvalidateSelection(const std::vector<SMALL_RECT>& rectangles) noexcept
{
    for (const auto& rect : rectangles)
    {
        RETURN_IF_FAILED(Invalidate(&rect));
    }

    return S_OK;
}

HRESULT GdiEngine::Invalidate(const SMALL_RECT* const psrRegion) noexcept
{
    RECT rcRegion = { 0 };
    RETURN_IF_FAILED(_ScaleByFont(psrRegion, &rcRegion));
    RETURN_HR(_InvalidateRect(&rcRegion));
}

HRESULT GdiEngine::InvalidateCursor(const COORD* const pcoordCursor) noexcept
{
    SMALL_RECT sr = Viewport::FromCoord(*pcoordCursor).ToExclusive();
    return this->Invalidate(&sr);
}

HRESULT GdiEngine::InvalidateAll() noexcept
{
    if (!_IsWindowValid())
    {
        return S_FALSE;
    }

    RECT rc;
    RETURN_HR_IF(E_FAIL, !(GetClientRect(_hwndTargetWindow, &rc)));
    RETURN_HR(InvalidateSystem(&rc));
}

HRESULT GdiEngine::InvalidateCircling(_Out_ bool* const pForcePaint) noexcept
{
    *pForcePaint = false;
    return S_FALSE;
}

HRESULT GdiEngine::PrepareForTeardown(_Out_ bool* const pForcePaint) noexcept
{
    *pForcePaint = false;
    return S_FALSE;
}

HRESULT GdiEngine::_InvalidCombine(const RECT* const prc) noexcept
{
    if (!_fInvalidRectUsed)
    {
        _rcInvalid = *prc;
        _fInvalidRectUsed = true;
    }
    else
    {
        _OrRect(&_rcInvalid, prc);
    }

    RETURN_IF_FAILED(_InvalidRestrict());

    return S_OK;
}

HRESULT GdiEngine::_InvalidOffset(const POINT* const ppt) noexcept
{
    if (_fInvalidRectUsed)
    {
        RECT rcInvalidNew;

        RETURN_IF_FAILED(LongAdd(_rcInvalid.left, ppt->x, &rcInvalidNew.left));
        RETURN_IF_FAILED(LongAdd(_rcInvalid.right, ppt->x, &rcInvalidNew.right));
        RETURN_IF_FAILED(LongAdd(_rcInvalid.top, ppt->y, &rcInvalidNew.top));
        RETURN_IF_FAILED(LongAdd(_rcInvalid.bottom, ppt->y, &rcInvalidNew.bottom));

        UnionRect(&_rcInvalid, &_rcInvalid, &rcInvalidNew);

        RETURN_IF_FAILED(_InvalidRestrict());
    }

    return S_OK;
}

HRESULT GdiEngine::_InvalidRestrict() noexcept
{
    RECT rcClient;

    RETURN_HR_IF(E_FAIL, !(GetClientRect(_hwndTargetWindow, &rcClient)));

    _rcInvalid.left = std::clamp(_rcInvalid.left, rcClient.left, rcClient.right);
    _rcInvalid.right = std::clamp(_rcInvalid.right, rcClient.left, rcClient.right);
    _rcInvalid.top = std::clamp(_rcInvalid.top, rcClient.top, rcClient.bottom);
    _rcInvalid.bottom = std::clamp(_rcInvalid.bottom, rcClient.top, rcClient.bottom);

    return S_OK;
}

HRESULT GdiEngine::_InvalidateRect(const RECT* const prc) noexcept
{
    RETURN_HR(_InvalidCombine(prc));
}
