<template>
  <div class="block">
    <el-pagination
      @size-change="handleSizeChange"
      @current-change="handleCurrentChange"
      :current-page.sync="currentPage"
      :page-size="size"
      layout="prev, pager, next, jumper"
      :total="total">
    </el-pagination>
  </div>
</template>

<script>
export default {
  data () {
    return {}
  },
  props: {
    total: Number,
    size: Number,
    page: Number
  },
  computed: {
    currentPage: {
      get: function () {
        return parseInt(this.page) | 1
      },
      set: function (nVal) {
        this.page = nVal
      }
    }
  },
  methods: {
    handleSizeChange (val) {
      console.log(val)
    },
    handleCurrentChange (val) {
      // console.log(val)
    }
  }
}
</script>

<style>
</style>
