#define LIB_NAME "Yoga"
#define MODULE_NAME "yoga"

#include <dmsdk/sdk.h>
#include <dmsdk/gui/gui.h>
#include <dmsdk/script/script.h>
#include <dmsdk/dlib/hash.h>
#include <dmsdk/dlib/hashtable.h>
#include "./yoga/Yoga.h"

bool g_InvertY = true;
dmHashTable32<YGNodeRef> g_YGNodes;

static YGFlexDirection GetInvertedFlexDirection(YGFlexDirection direction)
{
    if (g_InvertY && direction == YGFlexDirectionColumn)
    {
        return YGFlexDirectionColumnReverse;
    }
    else if (g_InvertY && direction == YGFlexDirectionColumnReverse)
    {
        return YGFlexDirectionColumn;
    }

    return direction;
}

static int SetInvertY(lua_State *L)
{
    g_InvertY = lua_toboolean(L, 2);

    return 0;
}

static void SetCapacityInternal(int n)
{
    g_YGNodes.SetCapacity(n, n);
}

static int SetCapacity(lua_State *L)
{
    SetCapacityInternal(luaL_checkinteger(L, 2));

    return 0;
}

static YGEdge GetInvertedEdge(YGEdge edge)
{
    if (g_InvertY && edge == YGEdgeTop)
    {
        return YGEdgeBottom;
    }
    else if (g_InvertY && edge == YGEdgeBottom)
    {
        return YGEdgeTop;
    }

    return edge;
}

static YGEdge GetEdge(lua_State *L)
{
    YGEdge edge = static_cast<YGEdge>(luaL_checkinteger(L, 2));

    return GetInvertedEdge(edge);
}

static YGNodeRef CheckYGNode(lua_State *L)
{
    dmGui::HNode node = dmGui::LuaCheckNode(L, 1);
    YGNodeRef *item = g_YGNodes.Get(node);
    
    if (item == NULL || *item == NULL)
    {
        luaL_error(L, "Could not find YGNodeRef. Was it manually freed?");
        return NULL;
    }

    return *item;
}

static int NewNode(lua_State *L)
{
    dmGui::HScene scene = dmGui::LuaCheckScene(L);
    dmGui::HNode node = dmGui::LuaCheckNode(L, 1);
    YGNodeRef ygNode = YGNodeNew();
    if (g_InvertY)
    {
        YGNodeStyleSetFlexDirection(ygNode, YGFlexDirectionColumnReverse);
    }
    g_YGNodes.Put(node, ygNode);

    return 0;
}

static int FreeNode(lua_State *L)
{
    dmGui::HNode node = dmGui::LuaCheckNode(L, 1);
    YGNodeRef *ygNode = g_YGNodes.Get(node);

    if (ygNode != NULL)
    {
        YGNodeFree(*ygNode);
        g_YGNodes.Erase(node);
    }

    return 0;
}

static int ResetNode(lua_State *L)
{
    dmGui::HNode node = dmGui::LuaCheckNode(L, 1);
    YGNodeRef *ygNode = g_YGNodes.Get(node);

    if (ygNode != NULL)
    {
        YGNodeReset(*ygNode);
    }

    return 0;
}

static int GetDirection(lua_State *L)
{
    YGNodeRef node = CheckYGNode(L);
    lua_pushinteger(L, YGNodeStyleGetDirection(node));

    return 1;
}

static int SetDirection(lua_State *L)
{
    YGNodeRef node = CheckYGNode(L);
    YGNodeStyleSetDirection(node, static_cast<YGDirection>(luaL_checkinteger(L, 2)));

    return 0;
}

static int GetOverflow(lua_State *L)
{
    YGNodeRef node = CheckYGNode(L);
    lua_pushinteger(L, YGNodeStyleGetOverflow(node));

    return 1;
}

static int SetOverflow(lua_State *L)
{
    YGNodeRef node = CheckYGNode(L);
    YGNodeStyleSetOverflow(node, static_cast<YGOverflow>(luaL_checkinteger(L, 2)));

    return 0;
}

static int GetDisplay(lua_State *L)
{
    YGNodeRef node = CheckYGNode(L);
    lua_pushinteger(L, YGNodeStyleGetDisplay(node));

    return 1;
}

static int SetDisplay(lua_State *L)
{
    YGNodeRef node = CheckYGNode(L);
    YGNodeStyleSetDisplay(node, static_cast<YGDisplay>(luaL_checkinteger(L, 2)));

    return 0;
}

static int GetPositionType(lua_State *L)
{
    YGNodeRef node = CheckYGNode(L);
    lua_pushinteger(L, YGNodeStyleGetPositionType(node));

    return 1;
}

static int SetPositionType(lua_State *L)
{
    YGNodeRef node = CheckYGNode(L);
    YGNodeStyleSetPositionType(node, static_cast<YGPositionType>(luaL_checkinteger(L, 2)));

    return 0;
}

static int GetPosition(lua_State *L)
{
    YGNodeRef node = CheckYGNode(L);
    YGEdge edge = GetEdge(L);
    YGValue value = YGNodeStyleGetPosition(node, edge);
    lua_pushnumber(L, value.value);

    return 1;
}

static int SetPosition(lua_State *L)
{
    YGNodeRef node = CheckYGNode(L);
    YGEdge edge = GetEdge(L);
    float value = luaL_checknumber(L, 3);
    YGNodeStyleSetPosition(node, edge, value);

    return 0;
}

static int SetPositionPercent(lua_State *L)
{
    YGNodeRef node = CheckYGNode(L);
    YGEdge edge = GetEdge(L);
    float value = luaL_checknumber(L, 3);
    YGNodeStyleSetPositionPercent(node, edge, value);

    return 0;
}

static int GetFlexDirection(lua_State *L)
{
    YGNodeRef node = CheckYGNode(L);
    lua_pushinteger(L, YGNodeStyleGetFlexDirection(node));

    return 1;
}

static int SetFlexDirection(lua_State *L)
{
    YGNodeRef node = CheckYGNode(L);
    YGFlexDirection direction = GetInvertedFlexDirection(static_cast<YGFlexDirection>(luaL_checkinteger(L, 2)));
    YGNodeStyleSetFlexDirection(node, direction);

    return 0;
}

static int SetFlexWrap(lua_State *L)
{
    YGNodeRef node = CheckYGNode(L);
    YGNodeStyleSetFlexWrap(node, static_cast<YGWrap>(luaL_checkinteger(L, 2)));

    return 0;
}

static int GetFlexWrap(lua_State *L)
{
    YGNodeRef node = CheckYGNode(L);
    lua_pushinteger(L, YGNodeStyleGetFlexWrap(node));

    return 1;
}

static int SetAlignContent(lua_State *L)
{
    YGNodeRef node = CheckYGNode(L);
    YGNodeStyleSetAlignContent(node, static_cast<YGAlign>(luaL_checkinteger(L, 2)));

    return 0;
}

static int GetAlignContent(lua_State *L)
{
    YGNodeRef node = CheckYGNode(L);
    lua_pushinteger(L, YGNodeStyleGetAlignContent(node));

    return 1;
}

static int GetAlignItems(lua_State *L)
{
    YGNodeRef node = CheckYGNode(L);
    lua_pushinteger(L, YGNodeStyleGetAlignItems(node));

    return 1;
}

static int SetAlignItems(lua_State *L)
{
    YGNodeRef node = CheckYGNode(L);
    YGNodeStyleSetAlignItems(node, static_cast<YGAlign>(luaL_checkinteger(L, 2)));

    return 0;
}

static int GetAlignSelf(lua_State *L)
{
    YGNodeRef node = CheckYGNode(L);
    lua_pushinteger(L, YGNodeStyleGetAlignSelf(node));

    return 1;
}

static int SetAlignSelf(lua_State *L)
{
    YGNodeRef node = CheckYGNode(L);
    YGNodeStyleSetAlignSelf(node, static_cast<YGAlign>(luaL_checkinteger(L, 2)));

    return 0;
}

static int GetJustifyContent(lua_State *L)
{
    YGNodeRef node = CheckYGNode(L);
    lua_pushinteger(L, YGNodeStyleGetJustifyContent(node));

    return 1;
}

static int SetJustifyContent(lua_State *L)
{
    YGNodeRef node = CheckYGNode(L);
    YGNodeStyleSetJustifyContent(node, static_cast<YGJustify>(luaL_checkinteger(L, 2)));

    return 0;
}

static int SetFlex(lua_State *L)
{
    YGNodeRef node = CheckYGNode(L);
    YGNodeStyleSetFlex(node, static_cast<YGAlign>(luaL_checkinteger(L, 2)));

    return 0;
}

static int GetFlex(lua_State *L)
{
    YGNodeRef node = CheckYGNode(L);
    lua_pushinteger(L, YGNodeStyleGetFlex(node));

    return 1;
}

static int GetGrow(lua_State *L)
{
    YGNodeRef node = CheckYGNode(L);
    lua_pushnumber(L, YGNodeStyleGetFlexGrow(node));

    return 1;
}

static int SetGrow(lua_State *L)
{
    YGNodeRef node = CheckYGNode(L);
    YGNodeStyleSetFlexGrow(node, luaL_checknumber(L, 2));

    return 0;
}

static int GetShrink(lua_State *L)
{
    YGNodeRef node = CheckYGNode(L);
    lua_pushnumber(L, YGNodeStyleGetFlexShrink(node));

    return 1;
}

static int SetShrink(lua_State *L)
{
    YGNodeRef node = CheckYGNode(L);
    YGNodeStyleSetFlexShrink(node, luaL_checknumber(L, 2));

    return 0;
}

static int GetBasis(lua_State *L)
{
    YGNodeRef node = CheckYGNode(L);
    YGValue basis = YGNodeStyleGetFlexBasis(node);
    lua_pushnumber(L, basis.value);

    return 1;
}

static int SetBasis(lua_State *L)
{
    YGNodeRef node = CheckYGNode(L);
    YGNodeStyleSetFlexBasis(node, luaL_checknumber(L, 2));

    return 0;
}

static int SetBasisPercent(lua_State *L)
{
    YGNodeRef node = CheckYGNode(L);
    YGNodeStyleSetFlexBasisPercent(node, luaL_checknumber(L, 2));

    return 0;
}

static int GetWidth(lua_State *L)
{
    YGNodeRef node = CheckYGNode(L);
    YGValue width = YGNodeStyleGetWidth(node);
    lua_pushnumber(L, width.value);

    return 1;
}

static int SetWidth(lua_State *L)
{
    YGNodeRef node = CheckYGNode(L);
    YGNodeStyleSetWidth(node, luaL_checknumber(L, 2));

    return 0;
}

static int GetMinWidth(lua_State *L)
{
    YGNodeRef node = CheckYGNode(L);
    YGValue minWidth = YGNodeStyleGetMinWidth(node);
    lua_pushnumber(L, minWidth.value);

    return 1;
}

static int SetMinWidth(lua_State *L)
{
    YGNodeRef node = CheckYGNode(L);
    YGNodeStyleSetMinWidth(node, luaL_checknumber(L, 2));

    return 0;
}

static int GetMaxWidth(lua_State *L)
{
    YGNodeRef node = CheckYGNode(L);
    YGValue maxWidth = YGNodeStyleGetMaxWidth(node);
    lua_pushnumber(L, maxWidth.value);

    return 1;
}

static int SetMaxWidth(lua_State *L)
{
    YGNodeRef node = CheckYGNode(L);
    YGNodeStyleSetMaxWidth(node, luaL_checknumber(L, 2));

    return 0;
}

static int SetWidthPercent(lua_State *L)
{
    YGNodeRef node = CheckYGNode(L);
    YGNodeStyleSetWidthPercent(node, luaL_checknumber(L, 2));

    return 0;
}

static int SetMinWidthPercent(lua_State *L)
{
    YGNodeRef node = CheckYGNode(L);
    YGNodeStyleSetMinWidthPercent(node, luaL_checknumber(L, 2));

    return 0;
}

static int SetMaxWidthPercent(lua_State *L)
{
    YGNodeRef node = CheckYGNode(L);
    YGNodeStyleSetMaxWidthPercent(node, luaL_checknumber(L, 2));

    return 0;
}

static int GetHeight(lua_State *L)
{
    YGNodeRef node = CheckYGNode(L);
    YGValue height = YGNodeStyleGetHeight(node);
    lua_pushnumber(L, height.value);

    return 1;
}

static int SetHeight(lua_State *L)
{
    YGNodeRef node = CheckYGNode(L);
    YGNodeStyleSetHeight(node, luaL_checknumber(L, 2));

    return 0;
}

static int GetMinHeight(lua_State *L)
{
    YGNodeRef node = CheckYGNode(L);
    YGValue minHeight = YGNodeStyleGetMinHeight(node);
    lua_pushnumber(L, minHeight.value);

    return 1;
}

static int SetMinHeight(lua_State *L)
{
    YGNodeRef node = CheckYGNode(L);
    YGNodeStyleSetMinHeight(node, luaL_checknumber(L, 2));

    return 0;
}

static int GetMaxHeight(lua_State *L)
{
    YGNodeRef node = CheckYGNode(L);
    YGValue maxHeight = YGNodeStyleGetMaxHeight(node);
    lua_pushnumber(L, maxHeight.value);

    return 1;
}

static int SetMaxHeight(lua_State *L)
{
    YGNodeRef node = CheckYGNode(L);
    YGNodeStyleSetMaxHeight(node, luaL_checknumber(L, 2));

    return 0;
}

static int SetHeightPercent(lua_State *L)
{
    YGNodeRef node = CheckYGNode(L);
    YGNodeStyleSetHeightPercent(node, luaL_checknumber(L, 2));

    return 0;
}

static int SetMinHeightPercent(lua_State *L)
{
    YGNodeRef node = CheckYGNode(L);
    YGNodeStyleSetMinHeightPercent(node, luaL_checknumber(L, 2));

    return 0;
}

static int SetMaxHeightPercent(lua_State *L)
{
    YGNodeRef node = CheckYGNode(L);
    YGNodeStyleSetMaxHeightPercent(node, luaL_checknumber(L, 2));

    return 0;
}

static int SetWidthHeight(lua_State *L)
{
    YGNodeRef node = CheckYGNode(L);
    YGNodeStyleSetWidth(node, luaL_checknumber(L, 2));
    YGNodeStyleSetHeight(node, luaL_checknumber(L, 3));

    return 0;
}

static int GetBorder(lua_State *L)
{
    YGNodeRef node = CheckYGNode(L);
    YGEdge edge = GetEdge(L);
    lua_pushnumber(L, YGNodeStyleGetBorder(node, edge));

    return 1;
}

static int SetBorder(lua_State *L)
{
    YGNodeRef node = CheckYGNode(L);
    YGEdge edge = GetEdge(L);
    float value = luaL_checknumber(L, 3);
    YGNodeStyleSetBorder(node, edge, value);

    return 0;
}

static int GetPadding(lua_State *L)
{
    YGNodeRef node = CheckYGNode(L);
    YGEdge edge = GetEdge(L);
    YGValue padding = YGNodeStyleGetPadding(node, edge);
    lua_pushnumber(L, padding.value);

    return 1;
}

static int SetPadding(lua_State *L)
{
    YGNodeRef node = CheckYGNode(L);
    YGEdge edge = GetEdge(L);
    float value = luaL_checknumber(L, 3);
    YGNodeStyleSetPadding(node, edge, value);

    return 0;
}

static int SetPaddingPercent(lua_State *L)
{
    YGNodeRef node = CheckYGNode(L);
    YGEdge edge = GetEdge(L);
    float value = luaL_checknumber(L, 3);
    YGNodeStyleSetPaddingPercent(node, edge, value);

    return 0;
}

static int GetMargin(lua_State *L)
{
    YGNodeRef node = CheckYGNode(L);
    YGEdge edge = GetEdge(L);
    YGValue margin = YGNodeStyleGetMargin(node, edge);
    lua_pushnumber(L, margin.value);

    return 1;
}

static int SetMargin(lua_State *L)
{
    YGNodeRef node = CheckYGNode(L);
    YGEdge edge = GetEdge(L);
    float value = luaL_checknumber(L, 3);
    YGNodeStyleSetMargin(node, edge, value);

    return 0;
}

static int SetMarginPercent(lua_State *L)
{
    YGNodeRef node = CheckYGNode(L);
    YGEdge edge = GetEdge(L);
    float value = luaL_checknumber(L, 3);
    YGNodeStyleSetMarginPercent(node, edge, value);

    return 0;
}

static int GetAspectRatio(lua_State *L)
{
    YGNodeRef node = CheckYGNode(L);
    lua_pushnumber(L, YGNodeStyleGetAspectRatio(node));

    return 1;
}

static int SetAspectRatio(lua_State *L)
{
    YGNodeRef node = CheckYGNode(L);
    YGNodeStyleSetAspectRatio(node, luaL_checknumber(L, 2));

    return 0;
}

static int CalculateLayout(lua_State *L)
{
    dmGui::HScene scene = dmGui::LuaCheckScene(L);
    dmGui::HNode node = dmGui::LuaCheckNode(L, 1);
    YGNodeRef *ygNode = g_YGNodes.Get(node);

    assert(ygNode != NULL);

    YGNodeCalculateLayout(*ygNode, YGUndefined, YGUndefined, YGDirectionLTR);

    return 0;
}

static int GetLayoutLeft(lua_State *L)
{
    YGNodeRef node = CheckYGNode(L);
    lua_pushnumber(L, YGNodeLayoutGetLeft(node));

    return 1;
}

static int GetLayoutTop(lua_State *L)
{
    YGNodeRef node = CheckYGNode(L);
    lua_pushnumber(L, YGNodeLayoutGetTop(node));

    return 1;
}

static int GetLayoutRight(lua_State *L)
{
    YGNodeRef node = CheckYGNode(L);
    lua_pushnumber(L, YGNodeLayoutGetRight(node));

    return 1;
}

static int GetLayoutBottom(lua_State *L)
{
    YGNodeRef node = CheckYGNode(L);
    lua_pushnumber(L, YGNodeLayoutGetBottom(node));

    return 1;
}

static int GetLayoutWidth(lua_State *L)
{
    YGNodeRef node = CheckYGNode(L);
    lua_pushnumber(L, YGNodeLayoutGetWidth(node));

    return 1;
}

static int GetLayoutHeight(lua_State *L)
{
    YGNodeRef node = CheckYGNode(L);
    lua_pushnumber(L, YGNodeLayoutGetHeight(node));

    return 1;
}

static int GetLayoutBorder(lua_State *L)
{
    YGNodeRef node = CheckYGNode(L);
    YGEdge edge = GetEdge(L);
    lua_pushnumber(L, YGNodeLayoutGetBorder(node, edge));

    return 1;
}

static int GetLayoutMargin(lua_State *L)
{
    YGNodeRef node = CheckYGNode(L);
    YGEdge edge = GetEdge(L);
    lua_pushnumber(L, YGNodeLayoutGetMargin(node, edge));

    return 1;
}

static int GetLayoutPadding(lua_State *L)
{
    YGNodeRef node = CheckYGNode(L);
    YGEdge edge = GetEdge(L);
    lua_pushnumber(L, YGNodeLayoutGetPadding(node, edge));

    return 1;
}

static int GetLayout(lua_State *L)
{
    YGNodeRef node = CheckYGNode(L);

    if (node == NULL)
    {
        return 0;
    }

    lua_newtable(L);

    lua_pushstring(L, "x");
    lua_pushnumber(L, YGNodeLayoutGetLeft(node));
    lua_rawset(L, -3);

    lua_pushstring(L, "y");
    lua_pushnumber(L, YGNodeLayoutGetTop(node));
    lua_rawset(L, -3);

    lua_pushstring(L, "width");
    lua_pushnumber(L, YGNodeLayoutGetWidth(node));
    lua_rawset(L, -3);

    lua_pushstring(L, "height");
    lua_pushnumber(L, YGNodeLayoutGetHeight(node));
    lua_rawset(L, -3);

    return 1;
}

static void UpdateNodeInternal(dmGui::HScene scene, dmGui::HNode dmNode, YGNodeRef ygNode)
{
    float width = YGNodeLayoutGetWidth(ygNode);
    float height = YGNodeLayoutGetHeight(ygNode);
    float x = YGNodeLayoutGetLeft(ygNode) + width / 2;
    float y = YGNodeLayoutGetTop(ygNode) + height / 2;

    YGNodeRef parent = YGNodeGetParent(ygNode);
    if (parent != NULL)
    {
        x -= YGNodeLayoutGetWidth(parent) / 2;
        y -= YGNodeLayoutGetHeight(parent) / 2;
    }

    SetNodeProperty(scene, dmNode, dmGui::PROPERTY_SIZE, dmVMath::Vector4(width, height, 0, 0));
    SetNodeProperty(scene, dmNode, dmGui::PROPERTY_POSITION, dmVMath::Vector4(x, y, 0, 0));

    // update all children nodes
    dmGui::HNode child = GetFirstChildNode(scene, dmNode);
    while (child != dmGui::INVALID_HANDLE)
    {
        YGNodeRef *ygChild = g_YGNodes.Get(child);
        if (ygChild != NULL)
        {
            UpdateNodeInternal(scene, child, *ygChild);
        }
        child = GetNextNode(scene, child);
    }
}

static int UpdateNode(lua_State *L)
{
    dmGui::HScene scene = dmGui::LuaCheckScene(L);
    dmGui::HNode node = dmGui::LuaCheckNode(L, 1);
    YGNodeRef *ygNode = g_YGNodes.Get(node);

    assert(ygNode != NULL);

    UpdateNodeInternal(scene, node, *ygNode);

    return 0;
}

static void EraseLookups(dmGui::HScene scene, dmGui::HNode node)
{
    dmGui::HNode child = GetFirstChildNode(scene, node);
    while (child != dmGui::INVALID_HANDLE)
    {
        g_YGNodes.Erase(child);
        EraseLookups(scene, child);
        child = GetNextNode(scene, child);
    }
}

static int DeleteNode(lua_State *L)
{
    dmGui::HScene scene = dmGui::LuaCheckScene(L);
    dmGui::HNode node = dmGui::LuaCheckNode(L, 1);
    YGNodeRef *ygNode = g_YGNodes.Get(node);
    EraseLookups(scene, node);
    if (ygNode != NULL)
    {
        g_YGNodes.Erase(node);
        YGNodeFreeRecursive(*ygNode);
    }
    DeleteNode(scene, node);

    return 0;
}

static int SetParent(lua_State *L)
{
    dmGui::HScene scene = dmGui::LuaCheckScene(L);
    dmGui::HNode node = dmGui::LuaCheckNode(L, 1);
    dmGui::HNode parent = dmGui::LuaCheckNode(L, 2);
    bool keep_scene_transform = lua_toboolean(L, 3);

    if (node != NULL && parent != NULL)
    {
        dmGui::SetNodeParent(scene, node, parent, false);

        YGNodeRef *p = g_YGNodes.Get(parent);
        YGNodeRef *c = g_YGNodes.Get(node);

        if (p != NULL && c != NULL)
        {
            YGNodeInsertChild(*p, *c, YGNodeGetChildCount(*p));
        }
    }

    return 0;
}

static int GetChildCount(lua_State *L)
{
    YGNodeRef node = CheckYGNode(L);
    lua_pushnumber(L, (lua_Number)YGNodeGetChildCount(node));

    return 1;
}

// YGNodeRef YGNodeNewWithConfig(YGConfigRef config);
// YGNodeRef YGNodeClone(YGNodeRef node);
// void YGNodeFreeRecursiveWithCleanupFunc(YGNodeRef node, YGNodeCleanupFunc cleanup);
// void YGNodeFreeRecursive(YGNodeRef node);
// void YGNodeInsertChild(YGNodeRef node, YGNodeRef child, uint32_t index);
// void YGNodeSwapChild(YGNodeRef node, YGNodeRef child, uint32_t index);
// void YGNodeRemoveChild(YGNodeRef node, YGNodeRef child);
// void YGNodeRemoveAllChildren(YGNodeRef node);
// YGNodeRef YGNodeGetChild(YGNodeRef node, uint32_t index);
// YGNodeRef YGNodeGetOwner(YGNodeRef node);
// YGNodeRef YGNodeGetParent(YGNodeRef node);
// uint32_t YGNodeGetChildCount(YGNodeRef node);
// void YGNodeSetChildren(YGNodeRef owner, const YGNodeRef children[], uint32_t count);
// void YGNodeSetChildren(YGNodeRef owner, const std::vector<YGNodeRef> &children);
// void YGNodeSetIsReferenceBaseline(YGNodeRef node, bool isReferenceBaseline);
// bool YGNodeIsReferenceBaseline(YGNodeRef node);
// void YGNodeMarkDirty(YGNodeRef node);
// void YGNodeMarkDirtyAndPropagateToDescendants(YGNodeRef node);
// void YGNodePrint(YGNodeRef node, YGPrintOptions options);
// bool YGFloatIsUndefined(float value);
// bool YGNodeCanUseCachedMeasurement(YGMeasureMode widthMode, float width, YGMeasureMode heightMode, float height, YGMeasureMode lastWidthMode, float lastWidth, YGMeasureMode lastHeightMode, float lastHeight, float lastComputedWidth, float lastComputedHeight, float marginRow, float marginColumn, YGConfigRef config);
// void YGNodeCopyStyle(YGNodeRef dstNode, YGNodeRef srcNode);
// void *YGNodeGetContext(YGNodeRef node);
// void YGNodeSetContext(YGNodeRef node, void *context);
// void YGConfigSetPrintTreeFlag(YGConfigRef config, bool enabled);
// bool YGNodeHasMeasureFunc(YGNodeRef node);
// void YGNodeSetMeasureFunc(YGNodeRef node, YGMeasureFunc measureFunc);
// bool YGNodeHasBaselineFunc(YGNodeRef node);
// void YGNodeSetBaselineFunc(YGNodeRef node, YGBaselineFunc baselineFunc);
// YGDirtiedFunc YGNodeGetDirtiedFunc(YGNodeRef node);
// void YGNodeSetDirtiedFunc(YGNodeRef node, YGDirtiedFunc dirtiedFunc);
// void YGNodeSetPrintFunc(YGNodeRef node, YGPrintFunc printFunc);
// bool YGNodeGetHasNewLayout(YGNodeRef node);
// void YGNodeSetHasNewLayout(YGNodeRef node, bool hasNewLayout);
// YGNodeType YGNodeGetNodeType(YGNodeRef node);
// void YGNodeSetNodeType(YGNodeRef node, YGNodeType nodeType);
// bool YGNodeIsDirty(YGNodeRef node);
// void YGNodeStyleSetFlexBasisAuto(YGNodeRef node);
// void YGNodeStyleSetMarginAuto(YGNodeRef node, YGEdge edge);
// void YGNodeStyleSetGap(YGNodeRef node, YGGutter gutter, float gapLength);
// float YGNodeStyleGetGap(YGNodeConstRef node, YGGutter gutter);
// void YGNodeStyleSetWidthAuto(YGNodeRef node);
// void YGNodeStyleSetHeightAuto(YGNodeRef node);
// YGDirection YGNodeLayoutGetDirection(YGNodeRef node);
// bool YGNodeLayoutGetHadOverflow(YGNodeRef node);
// void YGAssert(bool condition, const char *message);
// void YGAssertWithNode(YGNodeRef node, bool condition, const char *message);
// void YGAssertWithConfig(YGConfigRef config, bool condition, const char *message);
// YGConfigRef YGConfigNew(void);
// YGConfigRef YGConfigGetDefault(void);
// int32_t YGConfigGetInstanceCount(void);
// void YGConfigSetLogger(YGConfigRef config, YGLogger logger);
// void YGConfigSetPointScaleFactor(YGConfigRef config, float pixelsInPoint);
// bool YGConfigGetUseLegacyStretchBehaviour(YGConfigRef config);
// void YGConfigSetUseLegacyStretchBehaviour(YGConfigRef config, bool useLegacyStretchBehaviour);
// void YGConfigFree(YGConfigRef config);
// void YGConfigCopy(YGConfigRef dest, YGConfigRef src);
// void YGConfigSetExperimentalFeatureEnabled(YGConfigRef config, YGExperimentalFeature feature, bool enabled);
// bool YGConfigIsExperimentalFeatureEnabled(YGConfigRef config, YGExperimentalFeature feature);
// void YGConfigSetUseWebDefaults(YGConfigRef config, bool enabled);
// bool YGConfigGetUseWebDefaults(YGConfigRef config);
// void YGConfigSetCloneNodeFunc(YGConfigRef config, YGCloneNodeFunc callback);
// void YGConfigSetContext(YGConfigRef config, void *context);
// void *YGConfigGetContext(YGConfigRef config);
// float YGRoundValueToPixelGrid(double value, double pointScaleFactor, bool forceCeil, bool forceFloor);
// void YGTraversePreOrder(YGNodeRef node, std::function<void(YGNodeRef node)> &&f);

static int SetStyle(lua_State *L)
{
    //     YGNodeRef node = CheckYGNode(L);
    //
    //     lua_getfield(L, 2, "align_content");
    //     lua_getfield(L, 2, "align_items");
    //     lua_getfield(L, 2, "alpha");
    //     lua_getfield(L, 2, "aspect_ratio");
    //     lua_getfield(L, 2, "basis");
    //     lua_getfield(L, 2, "bottom");
    //     lua_getfield(L, 2, "direction");
    //     lua_getfield(L, 2, "display");
    //     lua_getfield(L, 2, "flex_direction");
    //     lua_getfield(L, 2, "flex_position");
    //     lua_getfield(L, 2, "flipbook_playback_rate");
    //     lua_getfield(L, 2, "grow");
    //     lua_getfield(L, 2, "height");
    //     lua_getfield(L, 2, "inner_radius");
    //     lua_getfield(L, 2, "justify_content");
    //     lua_getfield(L, 2, "leading");
    //     lua_getfield(L, 2, "left");
    //     lua_getfield(L, 2, "line_break");
    //     lua_getfield(L, 2, "margin_bottom");
    //     lua_getfield(L, 2, "margin_left");
    //     lua_getfield(L, 2, "margin_right");
    //     lua_getfield(L, 2, "margin_top");
    //     lua_getfield(L, 2, "margin");
    //     lua_getfield(L, 2, "max_height");
    //     lua_getfield(L, 2, "max_width");
    //     lua_getfield(L, 2, "min_height");
    //     lua_getfield(L, 2, "min_width");
    //     lua_getfield(L, 2, "outer_bounds");
    //     lua_getfield(L, 2, "overflow");
    //     lua_getfield(L, 2, "padding_bottom");
    //     lua_getfield(L, 2, "padding_left");
    //     lua_getfield(L, 2, "padding_right");
    //     lua_getfield(L, 2, "padding_top");
    //     lua_getfield(L, 2, "padding");
    //     lua_getfield(L, 2, "perimeter_vertices");
    //     lua_getfield(L, 2, "right");
    //     lua_getfield(L, 2, "shrink");
    //     lua_getfield(L, 2, "top");
    //     lua_getfield(L, 2, "tracking");
    //     lua_getfield(L, 2, "width");
    //
    //     lua_getfield(L, 2, "flipbook");
    //     lua_getfield(L, 2, "font");
    //     lua_getfield(L, 2, "particlefx");
    //     lua_getfield(L, 2, "texture");
    //
    //     lua_getfield(L, 2, "color");
    //     lua_getfield(L, 2, "outline");
    //     lua_getfield(L, 2, "rotation");
    //     lua_getfield(L, 2, "scale");
    //     lua_getfield(L, 2, "shadow");
    //     lua_getfield(L, 2, "slice9");
    //
    //     float align_content = luaL_checknumber(L, -50);
    //     float align_items = luaL_checknumber(L, -49);
    //     float alpha;
    //     float aspect_ratio;
    //     float basis;
    //     float bottom;
    //     float direction;
    //     float display;
    //     float flex_direction;
    //     float flex_position;
    //     float flipbook_playback_rate;
    //     float grow;
    //     float height;
    //     float inner_radius;
    //     float justify_content;
    //     float leading;
    //     float left;
    //     float line_break;
    //     float margin_bottom;
    //     float margin_left;
    //     float margin_right;
    //     float margin_top;
    //     float margin;
    //     float max_height;
    //     float max_width;
    //     float min_height;
    //     float min_width;
    //     float outer_bounds;
    //     float overflow;
    //     float padding_bottom;
    //     float padding_left;
    //     float padding_right;
    //     float padding_top;
    //     float padding;
    //     float perimeter_vertices;
    //     float right;
    //     float shrink;
    //     float top;
    //     float tracking;
    //     float width;

    // char *flipbook;
    // char *font;
    // char *particlefx;
    // char *texture;

    // float color;
    // float outline;
    // float rotation;
    // float scale;
    // float shadow;
    // float slice9;

    // Vector4* color;
    // if(color = dmScript::ToVector4(L, -1)) {
    //     printf("x: %f y: %f z: %f w: %f", color->getX(), color->getY(), color->getZ(), color->getW());
    // }

    // Vector4* v4;
    //     if ((v4 = dmScript::ToVector4(L, 2)))
    //     {
    //         Scene* scene = GuiScriptInstance_Check(L);
    //         SetNodeProperty(scene, hnode, PROPERTY_SLICE9, *v4);
    //     }
    //     else
    //     {
    //         luaL_error(L, "invalid parameter given");
    //     }

    // printf("width: %f, height: %f", width, height);

    // YGNodeRef node = CheckYGNode(L);
    // float value = luaL_checknumber(L, 3);

    return 0;
}

// Functions exposed to Lua
static const luaL_reg Module_methods[] =
    {
        // {"set_style", SetStyle},

        {"set_capacity", SetCapacity},
        {"set_invert_y", SetInvertY},

        {"new_node", NewNode},
        {"free_node", FreeNode},
        {"update_node", UpdateNode},
        {"delete_node", DeleteNode},
        {"reset_node", ResetNode},
        {"set_parent", SetParent},
        {"get_child_count", GetChildCount},

        {"get_overflow", GetOverflow},
        {"set_overflow", SetOverflow},

        {"get_direction", GetDirection},
        {"set_direction", SetDirection},

        {"get_flex_direction", GetFlexDirection},
        {"set_flex_direction", SetFlexDirection},

        {"get_align_items", GetAlignItems},
        {"set_align_items", SetAlignItems},

        {"get_align_content", GetAlignContent},
        {"set_align_content", SetAlignContent},

        {"get_justify_content", GetJustifyContent},
        {"set_justify_content", SetJustifyContent},

        {"get_grow", GetGrow},
        {"set_grow", SetGrow},

        {"get_shrink", GetShrink},
        {"set_shrink", SetShrink},

        {"get_basis", GetBasis},
        {"set_basis", SetBasis},
        {"set_basis_percent", SetBasisPercent},

        {"get_flex_position", GetPositionType},
        {"set_flex_position", SetPositionType},

        {"get_position", GetPosition},
        {"set_position", SetPosition},
        {"set_position_percent", SetPositionPercent},

        {"get_width", GetWidth},
        {"set_width", SetWidth},
        {"set_width_percent", SetWidthPercent},

        {"get_min_width", GetMinWidth},
        {"set_min_width", SetMinWidth},
        {"set_min_width_percent", SetMinWidthPercent},

        {"get_max_width", GetMaxWidth},
        {"set_max_width", SetMaxWidth},
        {"set_max_width_percent", SetMaxWidthPercent},

        {"get_height", GetHeight},
        {"set_height", SetHeight},
        {"set_height_percent", SetHeightPercent},

        {"get_min_height", GetMinHeight},
        {"set_min_height", SetMinHeight},
        {"set_min_height_percent", SetMinHeightPercent},

        {"get_max_height", GetMaxHeight},
        {"set_max_height", SetMaxHeight},
        {"set_max_height_percent", SetMaxHeightPercent},

        {"set_width_height", SetWidthHeight},

        {"get_aspect_ratio", GetAspectRatio},
        {"set_aspect_ratio", SetAspectRatio},

        {"get_border", GetBorder},
        {"set_border", SetBorder},

        {"get_margin", GetMargin},
        {"set_margin", SetMargin},
        {"set_margin_percent", SetMarginPercent},

        {"get_padding", GetPadding},
        {"set_padding", SetPadding},
        {"set_padding_percent", SetPaddingPercent},

        {"calculate_layout", CalculateLayout},
        {"get_layout", GetLayout},
        {"get_layout_left", GetLayoutLeft},
        {"get_layout_top", GetLayoutTop},
        {"get_layout_right", GetLayoutRight},
        {"get_layout_bottom", GetLayoutBottom},
        {"get_layout_width", GetLayoutWidth},
        {"get_layout_height", GetLayoutHeight},
        {"get_layout_border", GetLayoutBorder},
        {"get_layout_margin", GetLayoutMargin},
        {"get_layout_padding", GetLayoutPadding},

        {0, 0}};

static void LuaInit(lua_State *L)
{
#define SETCONSTANT(name, val)          \
    lua_pushnumber(L, (lua_Number)val); \
    lua_setfield(L, -2, #name);

    int top = lua_gettop(L);
    luaL_register(L, MODULE_NAME, Module_methods);

    SETCONSTANT(ALIGN_AUTO, YGAlignAuto);
    SETCONSTANT(ALIGN_START, YGAlignFlexStart);
    SETCONSTANT(ALIGN_CENTER, YGAlignCenter);
    SETCONSTANT(ALIGN_END, YGAlignFlexEnd);
    SETCONSTANT(ALIGN_STRETCH, YGAlignStretch);
    SETCONSTANT(ALIGN_BASELINE, YGAlignBaseline);
    SETCONSTANT(ALIGN_SPACE_BETWEEN, YGAlignSpaceBetween);
    SETCONSTANT(ALIGN_SPACE_AROUND, YGAlignSpaceAround);

    SETCONSTANT(DISPLAY_FLEX, YGDisplayFlex);
    SETCONSTANT(DISPLAY_NONE, YGDisplayNone);

    SETCONSTANT(DIRECTION_INHERIT, YGDirectionInherit);
    SETCONSTANT(DIRECTION_LTR, YGDirectionLTR);
    SETCONSTANT(DIRECTION_RTL, YGDirectionRTL);

    SETCONSTANT(EDGE_LEFT, YGEdgeLeft);
    SETCONSTANT(EDGE_TOP, YGEdgeTop);
    SETCONSTANT(EDGE_RIGHT, YGEdgeRight);
    SETCONSTANT(EDGE_BOTTOM, YGEdgeBottom);
    SETCONSTANT(EDGE_START, YGEdgeStart);
    SETCONSTANT(EDGE_END, YGEdgeEnd);
    SETCONSTANT(EDGE_HORIZONTAL, YGEdgeHorizontal);
    SETCONSTANT(EDGE_VERTICAL, YGEdgeVertical);
    SETCONSTANT(EDGE_ALL, YGEdgeAll);

    SETCONSTANT(FLEX_DIRECTION_COLUMN, YGFlexDirectionColumn);
    SETCONSTANT(FLEX_DIRECTION_COLUMN_REVERSE, YGFlexDirectionColumnReverse);
    SETCONSTANT(FLEX_DIRECTION_ROW, YGFlexDirectionRow);
    SETCONSTANT(FLEX_DIRECTION_ROW_REVERSE, YGFlexDirectionRowReverse);

    SETCONSTANT(JUSTIFY_START, YGJustifyFlexStart);
    SETCONSTANT(JUSTIFY_CENTER, YGJustifyCenter);
    SETCONSTANT(JUSTIFY_END, YGJustifyFlexEnd);
    SETCONSTANT(JUSTIFY_SPACE_BETWEEN, YGJustifySpaceBetween);
    SETCONSTANT(JUSTIFY_SPACE_AROUND, YGJustifySpaceAround);
    SETCONSTANT(JUSTIFY_SPACE_EVENLY, YGJustifySpaceEvenly);

    SETCONSTANT(OVERFLOW_VISIBLE, YGOverflowVisible);
    SETCONSTANT(OVERFLOW_HIDDEN, YGOverflowHidden);
    SETCONSTANT(OVERFLOW_SCROLL, YGOverflowScroll);

    SETCONSTANT(POSITION_TYPE_STATIC, YGPositionTypeStatic);
    SETCONSTANT(POSITION_TYPE_RELATIVE, YGPositionTypeRelative);
    SETCONSTANT(POSITION_TYPE_ABSOLUTE, YGPositionTypeAbsolute);

    SETCONSTANT(WRAP_NOWRAP, YGWrapNoWrap);
    SETCONSTANT(WRAP_WRAP, YGWrapWrap);
    SETCONSTANT(WRAP_WRAP_REVERSE, YGWrapWrapReverse);

    lua_pop(L, 1);
    assert(top == lua_gettop(L));
}

dmExtension::Result AppInitializeYoga(dmExtension::AppParams *params)
{
    return dmExtension::RESULT_OK;
}

dmExtension::Result InitializeYoga(dmExtension::Params *params)
{
    SetCapacityInternal(1024);
    LuaInit(params->m_L);
    printf("Registered %s Extension\n", MODULE_NAME);
    return dmExtension::RESULT_OK;
}

dmExtension::Result AppFinalizeYoga(dmExtension::AppParams *params)
{
    return dmExtension::RESULT_OK;
}

dmExtension::Result FinalizeYoga(dmExtension::Params *params)
{
    return dmExtension::RESULT_OK;
}

DM_DECLARE_EXTENSION(Yoga, LIB_NAME, AppInitializeYoga, AppFinalizeYoga, InitializeYoga, 0, 0, FinalizeYoga)