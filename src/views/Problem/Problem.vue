<template>
  <div class="table">
    <div class="body">
      <el-table
          :data="tableData"
          style="width: 100%"
          border
          fit
          >
          <el-table-column
            label="编号"
            width="100">
            <template slot-scope="scope">
              <span style="margin-left: 10px">{{ scope.row.id }}</span>
            </template>
          </el-table-column>
          <el-table-column
            label="标题">
            <template slot-scope="scope">
              <span style="margin-left: 10px">{{ scope.row.title }}</span>
            </template>
          </el-table-column>
          <el-table-column
            label="分类/来源">
            <template slot-scope="scope">
              <span style="margin-left: 10px">{{ scope.row.source }}</span>
            </template>
          </el-table-column>
          <el-table-column
            label="提交"
            width="80">
            <template slot-scope="scope">
              <span style="margin-left: 10px">{{ scope.row.submit }}</span>
            </template>
          </el-table-column>
          <el-table-column
            label="正确"
            width="80">
            <template slot-scope="scope">
              <span style="margin-left: 10px">{{ scope.row.accepted }}</span>
            </template>
          </el-table-column>
        </el-table>
    </div>
    <div class="footer">
      <Pagination :total="total" :size="size" :page="page"></Pagination>
    </div>
    </div>
</template>

<script>
import Pagination from '../../components/Pagination/Pagination'
import {
  mapState,
  mapActions
} from 'vuex'

export default {
  data () {
    return {
      page: 1
    }
  },
  computed: {
    tableData () {
      return this.problemList.data
    },
    ...mapState(['problemList']),
    total () {
      return this.problemList.total
    },
    size () {
      return this.problemList.limit
    }
  },
  components: {
    Pagination
  },
  mounted () {
    this.getProblemList(this.page)
  },
  methods: {
    ...mapActions(['getProblemList'])
  },
  watch: {
    page: function (oVal, nVal) {
      console.log(nVal)
    }
  }
}
</script>

<style>

</style>
